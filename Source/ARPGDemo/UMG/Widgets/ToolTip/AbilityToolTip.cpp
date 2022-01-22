// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityToolTip.h"

void UAbilityToolTip::NativeConstruct()
{
	Super::NativeConstruct();

	LevelChange.BindUFunction(this,TEXT("OnLevelChanged"));
}

void UAbilityToolTip::NativeDestruct()
{
	Super::NativeDestruct();

	if(LevelChange.IsBound())
	{
		LevelChange.Unbind();
	}
}

void UAbilityToolTip::OnLevelChanged(int NewLevel)
{
	Level->SetText(FText::FromString(FString::FromInt(NewLevel)));

	OnChangeCoolDown(NewLevel);
}
