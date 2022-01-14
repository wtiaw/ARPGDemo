// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBar.h"

UQuickReleaseContainer* USkillBar::GetQuickReleaseContainerByIndex(int Index)
{
	return  Cast<UQuickReleaseContainer>(QuickReleaseBar->GetChildAt(Index));
}

UQuickReleaseContainer* USkillBar::GetQuickReleaseContainerByGASAbilityInputID(EGASAbilityInputID GASAbilityInputID)
{
	for(auto i : QuickReleaseBar->GetAllChildren())
	{
		const auto QuickReleaseContainer = Cast<UQuickReleaseContainer>(i);
		if(QuickReleaseContainer->GASAbilityInputID == GASAbilityInputID)
		{
			return QuickReleaseContainer;
		}
	}
	return  nullptr;
}

TArray<UQuickReleaseContainer*> USkillBar::GetQuickReleaseContainersByTag(FGameplayTag Tag)
{
	TArray<UQuickReleaseContainer*> QuickReleaseContainers;
	
	for(auto i : QuickReleaseBar->GetAllChildren())
	{
		const auto QuickReleaseContainer = Cast<UQuickReleaseContainer>(i);
		if(QuickReleaseContainer->SkillItem->GetAbilityData().Tags.HasTag(Tag))
		{
			QuickReleaseContainers.Emplace(QuickReleaseContainer);
		}
	}
	return  QuickReleaseContainers;
}

