// Fill out your copyright notice in the Description page of Project Settings.


#include "WindowManager.h"

#include "MainWindow.h"
#include "ARPGDemo/GameMode/ARPGDemoGameMode.h"
#include "Blueprint/UserWidget.h"

class UMainWindow;

UWindowManager* UWindowManager::Instance = nullptr; 

UWindowManager::UWindowManager()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MainWindowClassFinder(TEXT("/Game/ARPGDemo/Blueprints/UMG/WBP_MainWindow"));
	if (MainWindowClassFinder.Succeeded())
		MainWindowClass = MainWindowClassFinder.Class;
}

void UWindowManager::BeginPlay()
{
	UMainWindow* MainWindow = CreateWidget<UMainWindow>(AARPGDemoGameMode::Instance->GetPlayerController(), MainWindowClass);
	MainWindow->AddToViewport();
}