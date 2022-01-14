// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityData.h"


FAbilityData::FAbilityData(): AbilityIcon(nullptr), Level(0)
{
}

FAbilityData::FAbilityData(FString AbilityName, FString AbilityDescription, UTexture2D* AbilityIcon, int Level, FGameplayTagContainer Tags, TSubclassOf<UGameplayAbility_Base> Ability): AbilityIcon(nullptr)
{
	this->AbilityName = AbilityName;
	this->AbilityDescription = AbilityDescription;
	this->AbilityIcon = AbilityIcon;
	this->Level = Level;
	this->Tags= Tags;
	this->Ability = Ability;
}

bool FAbilityData::bIsValid()
{
	return Ability ? true : false;
}
