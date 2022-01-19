// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickReleaseContainer.h"

#include "ARPGDemo/GameMode/PlayerState/ARPGDemoPlayerState.h"
#include "ARPGDemo/UMG/Widgets/Drag/Skill/SkillItem.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetTextLibrary.h"

void UQuickReleaseContainer::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetQuickName();
}

void UQuickReleaseContainer::NativeConstruct()
{
	Super::NativeConstruct();

	SkillItem->Parent = this;
}

void UQuickReleaseContainer::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (SkillItem->GetAbilityData().Ability)
	{
		auto PlayerState = UGameplayStatics::GetPlayerController(this, 0)->GetPlayerState<AARPGDemoPlayerState>();
		auto ASC = PlayerState->GetAbilitySystemComponent();

		FGameplayEffectQuery const Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(SkillItem->GetAbilityData().Tag);
		TArray<TPair<float, float>> DurationAndTimeRemaining = ASC->GetActiveEffectsTimeRemainingAndDuration(Query);

		if (DurationAndTimeRemaining.Num() > 0)
		{
			int32 BestIdx = 0;
			float LongestTime = DurationAndTimeRemaining[0].Key;
			for (int32 Idx = 1; Idx < DurationAndTimeRemaining.Num(); ++Idx)
			{
				if (DurationAndTimeRemaining[Idx].Key > LongestTime)
				{
					LongestTime = DurationAndTimeRemaining[Idx].Key;
					BestIdx = Idx;
				}
			}

			TimeRemaining = DurationAndTimeRemaining[BestIdx].Key;
			CooldownDuration = DurationAndTimeRemaining[BestIdx].Value;

			OnCoolDown();
		}
		else
		{
			Init();
		}
	}
	else
	{
		Init();
	}
}

bool UQuickReleaseContainer::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                          UDragDropOperation* InOperation)
{
	USkillItem* DraggedSkillItem = USkillItem::GetDraggedSkillItem(InOperation);

	if (DraggedSkillItem)
	{
		auto PlayerState = UGameplayStatics::GetPlayerController(this,0)->GetPlayerState<AARPGDemoPlayerState>();
		const auto TempData = SkillItem->GetAbilityData();
		const auto TempHandle = SkillItem->GetHandle();

		SkillItem->SetAbilityData(DraggedSkillItem);
		SkillItem->SetHandle(DraggedSkillItem->GetHandle());

		if (DraggedSkillItem->Parent)
		{
			DraggedSkillItem->SetAbilityData(TempData);
			DraggedSkillItem->SetHandle(TempHandle);
			
			PlayerState->SkillBarAbilityDatas[DraggedSkillItem->Parent->Index] = DraggedSkillItem->GetAbilityData();
		}
		PlayerState->SkillBarAbilityDatas[Index] = SkillItem->GetAbilityData();
		
		DraggedSkillItem->bIsDragSucceed = true;
	}
	return false;
}

void UQuickReleaseContainer::SetQuickName()
{
	QuickKey->SetText(FText::FromString(QuickKeyName));
}

void UQuickReleaseContainer::SetHighLight()
{
	Background->SetBrushTintColor(FLinearColor(1,1,1,1));
	QuickKeyBackground->SetBrushTintColor(FLinearColor(1,1,1,1));
	QuickKey->SetColorAndOpacity(FLinearColor(1,1,1,1));

	SkillItem->SetHighLight();
}

void UQuickReleaseContainer::HideHighLight()
{
	Background->SetBrushTintColor(FLinearColor(0.8,0.8,0.8,1));
	QuickKeyBackground->SetBrushTintColor(FLinearColor(0.8,0.8,0.8,1));
	QuickKey->SetColorAndOpacity(FLinearColor(0.8,0.8,0.8,1));

	SkillItem->HideHighLight();
}

void UQuickReleaseContainer::Init()
{
	CoolDown->SetVisibility(ESlateVisibility::Collapsed);

	auto Material = SkillItem->AbilityIcon->GetDynamicMaterial();
	Material->SetScalarParameterValue(FName(TEXT("PersentAge")), 1);
}

void UQuickReleaseContainer::OnCoolDown()
{
	CoolDown->SetVisibility(ESlateVisibility::HitTestInvisible);

	FString CD = FString::Printf(TEXT("%.1f"), TimeRemaining);
	CoolDown->SetText(FText::FromString(CD));

	auto Material = SkillItem->AbilityIcon->GetDynamicMaterial();
	Material->SetScalarParameterValue(FName(TEXT("PersentAge")), 1 - TimeRemaining / CooldownDuration);
}
