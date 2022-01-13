// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillItem.h"

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

FReply USkillItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// this->DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}

void USkillItem::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	const auto DragOperation = Cast<UDragOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(UDragOperation::StaticClass()));
	
	DragOperation->DraggedWidget = this;
	DragOperation->Pivot = EDragPivot::MouseDown;
	DragOperation->DefaultDragVisual = this;

	OutOperation = DragOperation;
	UE_LOG(LogTemp,Warning,TEXT("1"));
}

FAbilityData USkillItem::GetAbilityData()
{
	return AbilityData;
}

void USkillItem::SetAbilityData(USkillItem* SkillItem)
{
	AbilityData = SkillItem->GetAbilityData();
}

void USkillItem::SetAbilityData(FAbilityData InAbilityData)
{
	AbilityData = InAbilityData;
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
	AbilityIcon->SetBrushFromTexture(AbilityData.AbilityIcon);
}
