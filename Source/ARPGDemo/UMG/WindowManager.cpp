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

void UWindowManager::RegisterWindow(const EWindowTypes WindowType, UUserWidget* Window)
{
	if (WindowType == EWindowTypes::None)
	{
		UE_LOG(LogTemp, Error, TEXT("The window type of the window[%s] you want to register is null!"), *Window->GetName());
		return;
	}

	if (!Window)
	{
		UE_LOG(LogTemp, Error, TEXT("The window pointer of the window[WindowType: %s] you want to register is null!"), *StaticEnum<EWindowTypes>()->GetNameStringByValue((int64)WindowType));
		return;
	}

	WindowMap.Emplace(WindowType, Window);
}

UUserWidget* UWindowManager::GetWindow(const EWindowTypes WindowType)
{
	UUserWidget** ValuePointer = WindowMap.Find(WindowType);
	if (ValuePointer)
	{
		UUserWidget* Window = *ValuePointer;
		if (Window)
			return Window;
	}

	return nullptr;
}
