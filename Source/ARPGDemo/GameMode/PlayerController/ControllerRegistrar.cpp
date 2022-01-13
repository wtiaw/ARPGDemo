// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllerRegistrar.h"

#include "ARPGDemo/GameMode/ARPGDemoGameMode.h"
#include "ARPGDemo/UMG/Windows/WindowManager.h"
#include "ARPGDemo/UMG/Windows/BaseWindow/BaseWindow.h"
#include "ARPGDemo/UMG/Windows/MenuWindow/MainMenu.h"
#include "GameFramework/GameModeBase.h"

UControllerRegistrar* UControllerRegistrar::Instance = nullptr;

UControllerRegistrar* UControllerRegistrar::GetInstance()
{
	if (!Instance)
	{
		Instance = NewObject<UControllerRegistrar>();
		Instance->AddToRoot();
	}
	return Instance;
}

void UControllerRegistrar::Register()
{
	OpenMenuDelegate.AddDynamic(this,&UControllerRegistrar::OnOpenMenu);
	OpenSkillWindowDelegate.AddDynamic(this,&UControllerRegistrar::OnOpenSkillWindow);
}

void UControllerRegistrar::OnOpenMenu()
{
	TSubclassOf<UBaseWindow> MainMenuClass = LoadClass<UUserWidget>(
		NULL, TEXT("WidgetBlueprint'/Game/ARPGDemo/Blueprints/UMG/Windows/Menu/WBP_MainMenu.WBP_MainMenu_C'"));

	UMainMenu* MainMenu = Cast<UMainMenu>(CreateWidget(AARPGDemoGameMode::Instance->GetPlayerController(), MainMenuClass));
	MainMenu->AddToViewport();
}

void UControllerRegistrar::OnOpenSkillWindow()
{
	UWindowManager::Instance->OpenFloatingWindow(EWindowTypes::Floating_SkillWindow);
}
