// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickReleaseContainer.h"

bool UQuickReleaseContainer::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	USkillItem* DraggedSkillItem = USkillItem::GetDraggedSkillItem(InOperation);

	if(DraggedSkillItem)
	{
		SkillItem->SetAbilityData(DraggedSkillItem);

		SkillItem->SetIcon();
	}
	
	return false;
}

void UQuickReleaseContainer::SetQuickName()
{
	QuickKey->SetText(FText::FromString(QuickKeyName));
}
