// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityData.h"


FAbilityData::FAbilityData(): AbilityIcon(nullptr)
{
}

FAbilityData::FAbilityData(FString AbilityName, FString AbilityDescription, UTexture2D* AbilityIcon): AbilityIcon(nullptr)
{
	this->AbilityName = AbilityName;
	this->AbilityDescription = AbilityDescription;
	this->AbilityIcon = AbilityIcon;
}
