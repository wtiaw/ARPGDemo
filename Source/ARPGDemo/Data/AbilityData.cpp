// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityData.h"


FAbilityData::FAbilityData(): AbilityId(0), Level(0), MaxLevel(0), DamageType(), ElementalDamage(),
                              ActivatedIcon(nullptr),
                              InactivatedAbilityIcon(nullptr),
                              AbilityType(),
                              CoolDown(nullptr), Precondition(nullptr)
{
}

FAbilityData::FAbilityData(FString AbilityName, FString AbilityDescription, UTexture2D* ActivatedAbilityIcon, UTexture2D* InactivatedAbilityIcon, EAbilityType AbilityType, int Level, int MaxLevel, EDamageType DamageType, EElementalDamageType ElementalDamage, TSubclassOf<UGameplayAbility_Base> Ability, FGameplayTagContainer Tag, UCurveTable* CoolDown, UDataTable* Precondition)
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
	this->DamageType = DamageType;
	this->ElementalDamage = ElementalDamage;
	this->CoolDown = CoolDown;
	this->Precondition = Precondition;
}

bool FAbilityData::IsValid()
{
	return Ability ? true : false;
}
