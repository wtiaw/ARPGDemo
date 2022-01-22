// Fill out your copyright notice in the Description page of Project Settings.


#include "InputSetting.h"

void UInputSetting::ShowKey()
{
	SkillSwitch->SetActiveWidgetIndex(0);
}

void UInputSetting::ShowCircular()
{
	SkillSwitch->SetActiveWidgetIndex(1);
}

void UInputSetting::SetWarningText()
{
	Key->SetColorAndOpacity(FLinearColor(1,0,0,1));
}

void UInputSetting::SetNormalText()
{
	Key->SetColorAndOpacity(FLinearColor(1,1,1,1));
}
