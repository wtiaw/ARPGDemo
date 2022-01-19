// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickReleaseContainer.h"

#include "ARPGDemo/GameMode/PlayerState/ARPGDemoPlayerState.h"
#include "ARPGDemo/UMG/Widgets/Drag/Skill/SkillItem.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
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

	// CoolDownDelegate.BindDynamic(this, &UQuickReleaseContainer::OnCoolDown);
	// AbilityChanged.AddDynamic(this, &UQuickReleaseContainer::OnAbilityCoolDownChanged);
}

void UQuickReleaseContainer::NativeDestruct()
{
	Super::NativeDestruct();

	Init();

	CoolDownDelegate.Unbind();
	AbilityChanged.RemoveDynamic(this, &UQuickReleaseContainer::OnAbilityCoolDownChanged);
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
			
			PlayerState->AbilityHandles[DraggedSkillItem->Parent->Index] = DraggedSkillItem->GetHandle();
		}
		
		PlayerState->AbilityHandles[Index] = SkillItem->GetHandle();
		PlayerState->AbilityTags.AppendTags(SkillItem->GetAbilityData().Tags);
		
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

void UQuickReleaseContainer::OnAbilityCoolDownChanged()
{
	Init();

	auto PlayerState = Cast<AARPGDemoPlayerState>(UGameplayStatics::GetPlayerCharacter(this, 0)->GetPlayerState());

	// AsyncTask = UAsyncTaskCooldownChanged::ListenForCooldownChange(PlayerState->GetAbilitySystemComponent(),
	//                                                                SkillItem->GetAbilityData().Tags, false);
	
	AsyncTask->OnCooldownEnd.AddDynamic(this, &UQuickReleaseContainer::OnCoolDownBegin);
	AsyncTask->OnCooldownEnd.AddDynamic(this, &UQuickReleaseContainer::OnCoolDownEnd);
}

void UQuickReleaseContainer::OnCoolDownBegin(FGameplayTag CooldownTag, float TimeRemaining, float Duration)
{
	this->SkillTimeRemaining = Duration;
	this->SkillDuration = Duration;
	
	TimerHandle = UKismetSystemLibrary::K2_SetTimerDelegate(CoolDownDelegate,0.1,true);
	UE_LOG(LogTemp,Warning,TEXT("OnCoolDownBegin"));
	CoolDown->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UQuickReleaseContainer::OnCoolDownEnd(FGameplayTag CooldownTag, float TimeRemaining, float Duration)
{
	Init();
}

void UQuickReleaseContainer::Init()
{
 	if(TimerHandle.IsValid())
 	{
 		UKismetSystemLibrary::K2_ClearTimerHandle(this,TimerHandle);
 		CoolDown->SetVisibility(ESlateVisibility::Collapsed);

 		auto Material = SkillItem->AbilityIcon->GetDynamicMaterial();
 		Material->SetScalarParameterValue(FName(TEXT("PersentAge")),1);
 	}
}

void UQuickReleaseContainer::OnCoolDown()
{
	UE_LOG(LogTemp,Warning,TEXT("OnCoolDown"));
	SkillTimeRemaining -= 0.1;

	const FText CoolDownText = UKismetTextLibrary::Conv_FloatToText(SkillTimeRemaining, HalfToEven, 1, true, 324, 1, 1);
	CoolDown->SetText(CoolDownText);

	auto Material = SkillItem->AbilityIcon->GetDynamicMaterial();
	Material->SetScalarParameterValue(FName(TEXT("PersentAge")), SkillTimeRemaining / SkillDuration);
}
