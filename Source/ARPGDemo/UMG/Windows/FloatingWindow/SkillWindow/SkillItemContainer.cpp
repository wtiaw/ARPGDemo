// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillItemContainer.h"

void USkillItemContainer::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetAbilityData();
	SkillItem->AbilityData = AbilityData;

	SetLevelText();
	
	SkillItem->NativePreConstruct();
}

void USkillItemContainer::NativeConstruct()
{
	Super::NativeConstruct();

	SkillItem->GiveAbility();
}

void USkillItemContainer::SetAbilityData()
{
	if(AbilityDataTable)
	{
		if(auto Data = AbilityDataTable->FindRow<FAbilityData>(AbilityName,""))
		{
			AbilityData = Data;
		}
	}
}

void USkillItemContainer::SetLevelText()
{
	const int InLevel = AbilityData->Level;
	const int MaxLevel = AbilityData->MaxLevel;

	const FString LevelText = FString::Printf(TEXT("%d/%d"),InLevel,MaxLevel);

	Level->SetText(FText::FromString(LevelText));
}

void USkillItemContainer::LevelUp()
{
	if(CheckLevelUp())
	{
		AbilityData->Level++;
		SetLevelText();
		SkillItem->GiveAbility();
	}
}

void USkillItemContainer::LevelDown()
{
	if(CheckLevelDown())
	{
		AbilityData->Level--;
		SetLevelText();
		SkillItem->GiveAbility();
	}
}

bool USkillItemContainer::CheckLevelUp()
{
	return true;
}

bool USkillItemContainer::CheckLevelDown()
{
	return true;
}


