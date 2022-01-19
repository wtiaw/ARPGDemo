// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBar.h"
#include "GameplayTagsManager.h"
#include "ARPGDemo/UMG/Widgets/Drag/Skill/SkillItem.h"
#include "ARPGDemo/UMG/Windows/FixedWindow/Skill/QuickReleaseContainer.h"

void USkillBar::NativeConstruct()
{
	Super::NativeConstruct();
	
	CoolDownTags = UGameplayTagsManager::Get().RequestGameplayTagChildren(CoolDownTag);
	
	for(auto i : QuickReleaseBar->GetAllChildren())
	{
		Cast<UQuickReleaseContainer>(i)->Parent = this;
	}
}

UQuickReleaseContainer* USkillBar::GetQuickReleaseContainerByIndex(int Index)
{
	return  Cast<UQuickReleaseContainer>(QuickReleaseBar->GetChildAt(Index));
}


