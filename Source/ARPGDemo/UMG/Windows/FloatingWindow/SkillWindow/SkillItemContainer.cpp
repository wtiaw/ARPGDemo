// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillItemContainer.h"

#include "ARPGDemo/GameMode/ARPGDemoGameMode.h"

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

	Save = AARPGDemoGameMode::Instance->SaveGameInstance;
	
	if(Save)
	{
		//是否存在这个映射，如果不存在就添加，如果存在就更改等级
		if(!Save->SkillDatas.Contains(AbilityData->AbilityId))
		{
			Save->SkillDatas.Emplace(AbilityData->AbilityId,AbilityData->Level);
		}
		else
		{
			AbilityData->Level = Save->SkillDatas[AbilityData->AbilityId];
		}
	}
	
	SetLevelText();

	SkillItem->NativePreConstruct();
	
	CheckButton();
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
	if (AbilityData)
	{
		const int InLevel = AbilityData->Level;
		const int MaxLevel = AbilityData->MaxLevel;

		const FString LevelText = FString::Printf(TEXT("%d/%d"), InLevel, MaxLevel);

		Level->SetText(FText::FromString(LevelText));
	}
}

void USkillItemContainer::LevelUp()
{
	if(CheckLevelUp())
	{
		//修改节能功能等级，同时修改技能等级
		AbilityData->Level++;
		Save->SkillDatas[AbilityData->AbilityId] = AbilityData->Level;

		//设置技能等级文本
		SetLevelText();
		SkillItem->GiveAbility();
		SkillItem->SetIcon();

		CheckButton();
	}
}

void USkillItemContainer::LevelDown()
{
	if(CheckLevelDown())
	{
		//修改节能功能等级，同时修改技能等级
		AbilityData->Level--;
		Save->SkillDatas[AbilityData->AbilityId] = AbilityData->Level;

		//设置技能等级文本
		SetLevelText();
		SkillItem->GiveAbility();
		SkillItem->SetIcon();
		
		CheckButton();
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

void USkillItemContainer::CheckButton()
{
	if (AbilityData->Level == AbilityData->MaxLevel)
	{
		Btn_LevelUp->SetVisibility(ESlateVisibility::Hidden);
	}
	else if(AbilityData->Level == AbilityData->MinLevel)
	{
		Btn_LevelDown->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		Btn_LevelUp->SetVisibility(ESlateVisibility::Visible);
		Btn_LevelDown->SetVisibility(ESlateVisibility::Visible);
	}
}


