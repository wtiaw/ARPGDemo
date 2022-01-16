// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillItem.h"

#include "QuickReleaseContainer.h"
#include "ARPGDemo/GamePlayAbilitySystem/AbilityManager.h"
#include "ARPGDemo/UMG/Widgets/Drag/DragOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void USkillItem::NativeConstruct()
{
	Super::NativeConstruct();
}

void USkillItem::NativePreConstruct()
{
	Super::NativePreConstruct();
	
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
	
	if(AbilityData.AbilityIcon == nullptr)
	{
		Reply = FReply::Handled();
	}
	else
	{
		if(InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("1"));
			Reply =	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
		}
	}
	
	return Reply;
}

void USkillItem::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	const auto DragOperation = Cast<UDragOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(UDragOperation::StaticClass()));
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("DragDetected"));
	DragOperation->DraggedWidget = this;
	DragOperation->Pivot = EDragPivot::CenterCenter;
	DragOperation->DefaultDragVisual = this;

	this->SetVisibility(ESlateVisibility::HitTestInvisible);
	
	OutOperation = DragOperation;
}

void USkillItem::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if(Parent && !bIsDragSucceed)
	{
		UAbilityManager::GetInstance()->ClearAbility(Parent->GASAbilityInputID);
		SetAbilityData(FAbilityData());

		bIsDragSucceed = false;
	}
	this->SetVisibility(ESlateVisibility::Visible);
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("DragCancelled"));
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

FAbilityData USkillItem::GetAbilityData()
{
	return AbilityData;
}

void USkillItem::SetAbilityData(USkillItem* SkillItem)
{
	AbilityData = SkillItem->GetAbilityData();
	SetIcon();
}

void USkillItem::SetAbilityData(FAbilityData InAbilityData)
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

void USkillItem::SetIcon()
{
	AbilityIcon->SetBrushFromMaterial(Material);
	auto DynamicMaterial = AbilityIcon->GetDynamicMaterial();

	DynamicMaterial->SetTextureParameterValue(FName(TEXT("AbilityIcon")),AbilityData.AbilityIcon);
	DynamicMaterial->SetScalarParameterValue(FName(TEXT("PersentAge")),1);
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
