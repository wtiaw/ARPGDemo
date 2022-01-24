// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityData.h"


FAbilityData::FAbilityData(): AbilityId(0), Level(0), MinLevel(0), MaxLevel(0), DamageType(), ElementalDamage(),
                              ActivatedIcon(nullptr),
                              InactivatedAbilityIcon(nullptr),
                              AbilityType(),
                              CoolDown(nullptr),
                              Precondition(nullptr)
{
}

FAbilityData::FAbilityData(FString AbilityName, FString AbilityDescription, UTexture2D* ActivatedAbilityIcon, UTexture2D* InactivatedAbilityIcon, EAbilityType AbilityType, int Level, int MaxLevel, int MinLevel,  EDamageType DamageType, EElementalDamageType ElementalDamage, TSubclassOf<UGameplayAbility_Base> Ability, FGameplayTagContainer Tag, UCurveTable* CoolDown, UDataTable* Precondition)
{
	this->AbilityName = AbilityName;
	this->AbilityDescription = AbilityDescription;
	this->ActivatedIcon = ActivatedAbilityIcon;
	this->InactivatedAbilityIcon = InactivatedAbilityIcon;
	this->AbilityType = AbilityType;
	this->Level = Level;
	this->MaxLevel = MaxLevel;
	this->MinLevel = MinLevel;
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

FAbilityKeyData::FAbilityKeyData(): AbilityId(0), Level(0)
{
}

FAbilityKeyData::FAbilityKeyData(int AbilityId, int Level)
{
	this->AbilityId = AbilityId;
	this->Level = Level;
}
