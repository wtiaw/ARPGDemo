// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickReleaseContainer.h"

#include "ARPGDemo/GameMode/ARPGDemoGameMode.h"
#include "ARPGDemo/GamePlayAbilitySystem/AbilityManager.h"

void UQuickReleaseContainer::NativeConstruct()
{
	Super::NativeConstruct();

	SkillItem->Parent = this;
}

bool UQuickReleaseContainer::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                          UDragDropOperation* InOperation)
{
	USkillItem* DraggedSkillItem = USkillItem::GetDraggedSkillItem(InOperation);

	if (DraggedSkillItem)
	{
		const FAbilityData Temp = SkillItem->GetAbilityData();

		SkillItem->SetAbilityData(DraggedSkillItem);
		const auto SkillData = SkillItem->GetAbilityData();

		if (DraggedSkillItem->Parent)
		{
			DraggedSkillItem->SetAbilityData(Temp);

			UAbilityManager::GetInstance()->SwapAbility(DraggedSkillItem->Parent->GASAbilityInputID, GASAbilityInputID);

			if (DraggedSkillItem->Parent->AbilityChanged.IsBound())
				DraggedSkillItem->Parent->AbilityChanged.Broadcast();
		}
		else
		{
			UAbilityManager::GetInstance()->GiveAbility(GASAbilityInputID, SkillData.Ability, SkillData.Level);
		}

		if (AbilityChanged.IsBound())
			AbilityChanged.Broadcast();
		
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
