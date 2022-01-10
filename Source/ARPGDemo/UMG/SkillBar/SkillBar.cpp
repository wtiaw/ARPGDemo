// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBar.h"

#include "ARPGDemo/UMG/WindowManager.h"

USkillBar::USkillBar(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void USkillBar::NativeConstruct()
{
	Super::NativeConstruct();

	UWindowManager::Instance->RegisterWindow(EWindowTypes::SkillBarWindow,this);
}

void USkillBar::AbilityCoolDown()
{
	
}
