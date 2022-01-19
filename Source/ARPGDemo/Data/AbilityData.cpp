// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityData.h"


FAbilityData::FAbilityData(): ActivatedIcon(nullptr), InactivatedAbilityIcon(nullptr), AbilityType(), Level(0),
                              MaxLevel(0)
{
}

FAbilityData::FAbilityData(FString AbilityName, FString AbilityDescription, UTexture2D* ActivatedAbilityIcon, UTexture2D* InactivatedAbilityIcon, EAbilityType AbilityType, int Level, int MaxLevel, TSubclassOf<UGameplayAbility_Base> Ability, FGameplayTagContainer Tag):
	ActivatedIcon(nullptr), InactivatedAbilityIcon(nullptr)
{
	this->AbilityName = AbilityName;
	this->AbilityDescription = AbilityDescription;
	this->ActivatedIcon = ActivatedAbilityIcon;
	this->InactivatedAbilityIcon = InactivatedAbilityIcon;
	this->AbilityType = AbilityType;
	this->Level = Level;
	this->MaxLevel = MaxLevel;
	this->Ability = Ability;
	this->Tag = Tag;
}

bool FAbilityData::IsValid()
{
	return Ability ? true : false;
}
