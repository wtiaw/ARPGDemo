// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillItem.h"

#include "SkillItem_Visual.h"
#include "ARPGDemo/GamePlay/Gamming/PlayerState/ARPGDemoPlayerState.h"
#include "ARPGDemo/UMG/Widgets/Drag/DragOperation.h"
#include "ARPGDemo/UMG/Windows/FixedWindow/Skill/QuickReleaseContainer.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void USkillItem::NativeConstruct()
{
	Super::NativeConstruct();
}

void USkillItem::NativePreConstruct()
{
	Super::NativePreConstruct();
                                 	
    HighLight->SetBrushFromMaterial(HighLightTexture);
                                    
    SetIcon();
}

void USkillItem::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	SetHighLight();
}

void USkillItem::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	HideHighLight();
}

FReply USkillItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = FReply::Handled();


	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		if (AbilityData->Level > 0)
		{
			Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
		}
		else
		{
			Reply = FReply::Handled();
		}
	}

	return Reply;
}

void USkillItem::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                      UDragDropOperation*& OutOperation)
{
	const auto DragOperation = Cast<UDragOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(UDragOperation::StaticClass()));
	auto Visual = CreateWidget<USkillItem_Visual>(this,VisualClass);
	
	DragOperation->DraggedWidget = this;
	DragOperation->Pivot = EDragPivot::CenterCenter;
	DragOperation->DefaultDragVisual = Visual;
	
	Visual->AbilityIcon->SetBrushFromTexture(AbilityData->ActivatedIcon);
	
	OutOperation = DragOperation;
}

void USkillItem::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if(Parent && !bIsDragSucceed)
	{
		SetAbilityData(&DefaultData);

		auto PlayerState = UGameplayStatics::GetPlayerController(this,0)->GetPlayerState<AARPGDemoPlayerState>();
		
		PlayerState->SkillBarAbilityDatas[Parent->Index] = nullptr;
		
		bIsDragSucceed = false;
	}
}

void USkillItem::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                   UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	if(!bDragging)
	{
		SetHighLight();
	}
}

void USkillItem::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	HideHighLight();
}

FAbilityData* USkillItem::GetAbilityData()
{
	return AbilityData;
}

void USkillItem::GetAbilityData(FAbilityData& Out)
{
	Out = *AbilityData;
}

void USkillItem::SetAbilityData(USkillItem* SkillItem)
{
	AbilityData = SkillItem->GetAbilityData();
	SetIcon();
}

void USkillItem::SetAbilityData(FAbilityData* InAbilityData)
{
	AbilityData = InAbilityData;
	SetIcon();
}

USkillItem* USkillItem::GetDraggedSkillItem(UDragDropOperation* DragDropOperation)
{
	USkillItem* MovedItem = nullptr;
	const auto DragOperation = Cast<UDragOperation>(DragDropOperation);
	if (DragOperation)
	{
		const auto Item = Cast<USkillItem>(DragOperation->DraggedWidget);
		if (Item)
			MovedItem = Item;
	}
	return MovedItem;
}

FGameplayAbilitySpec* USkillItem::GetGameplayAbilitySpec()
{
	const auto PlayerController = UGameplayStatics::GetPlayerController(this,0);
	const auto PS = PlayerController->GetPlayerState<AARPGDemoPlayerState>();

	return PS->GetAbilitySystemComponent()->FindAbilitySpecFromClass(AbilityData->Ability);
}

void USkillItem::SetMaterial(UMaterialInstance* InMaterial)
{
	Material = InMaterial;
}

void USkillItem::SetIcon()
{
	AbilityIcon->SetBrushFromMaterial(Material);
	auto DynamicMaterial = AbilityIcon->GetDynamicMaterial();

	if (AbilityData)
	{
		if (AbilityData->Level > 0)
		{
			DynamicMaterial->SetTextureParameterValue(FName(TEXT("AbilityIcon")), AbilityData->ActivatedIcon);
		}
		else
		{
			DynamicMaterial->SetTextureParameterValue(FName(TEXT("AbilityIcon")), AbilityData->InactivatedAbilityIcon);
		}
	}
}

void USkillItem::SetHighLight() const
{
	AbilityIcon->SetBrushTintColor(FLinearColor(1,1,1,1));
	HighLight->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void USkillItem::HideHighLight() const
{
	AbilityIcon->SetBrushTintColor(FLinearColor(0.8,0.8,0.8,1));
	HighLight->SetVisibility(ESlateVisibility::Collapsed);
}

void USkillItem::GiveAbility(bool bTerminate)
{
	if (AbilityData->Ability && AbilityData->Level > 0)
	{
		const auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		const auto PS = PlayerController->GetPlayerState<AARPGDemoPlayerState>();

		const auto Ability = AbilityData->Ability;
		const auto Level = AbilityData->Level;

		const auto Spec = GetGameplayAbilitySpec();
		if (Spec)
		{
			if (bTerminate)
			{
				auto Handle = Spec->Handle;

				PS->GetAbilitySystemComponent()->ClearAbility(Handle);
				PS->GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(Ability, Level));
			}
			else
			{
				Spec->Level = AbilityData->Level;
			}
		}
		else
		{
			PS->GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(Ability, Level));
		}
	}
}
