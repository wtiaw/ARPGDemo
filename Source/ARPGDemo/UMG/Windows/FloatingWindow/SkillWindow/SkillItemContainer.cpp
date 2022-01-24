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

void USkillItemContainer::SetAbilityData()
{
	if(AbilityDataTable)
	{
		if(auto Data = AbilityDataTable->FindRow<FAbilityData>(AbilityName,""))
		{
			AbilityData = *Data;
		}
	}
}

void USkillItemContainer::SetLevelText()
{
	const int InLevel = AbilityData.Level;
	const int MaxLevel = AbilityData.MaxLevel;

	const FString LevelText = FString::Printf(TEXT("%d/%d"),InLevel,MaxLevel);

	Level->SetText(FText::FromString(LevelText));
}

void USkillItemContainer::LevelUp()
{
	if(CheckLevelUp())
	{
		AbilityData.Level++;
		
	}
}

void USkillItemContainer::LevelDown()
{
	if(CheckLevelDown())
	{
		UE_LOG(LogTemp,Warning,TEXT("LevelDown"));
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


