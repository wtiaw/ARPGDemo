// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWindow.h"

#include "WindowManager.h"
#include "WindowType.h"

void UMainWindow::NativeConstruct()
{
	Super::NativeConstruct();

	UWindowManager::Instance->RegisterWindow(EWindowTypes::MainWindow,this);
}

USkillBar* UMainWindow::GetSkillBar()
{
	return SkillBar;
}
