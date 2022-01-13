// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllerRegistrar.h"
#include "ARPGDemo/GameMode/ARPGDemoGameMode.h"
#include "ARPGDemo/UMG/Windows/WindowManager.h"
#include "ARPGDemo/UMG/Windows/BaseWindow/BaseWindow.h"
#include "ARPGDemo/UMG/Windows/HUD/HUDMouseCursor.h"
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
	ShowMouseCursor.AddDynamic(this,&UControllerRegistrar::OnShowMouseCursor);
    HideMouseCursor.AddDynamic(this,&UControllerRegistrar::OnHideMouseCursor);
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

void UControllerRegistrar::OnShowMouseCursor()
{
	UWindowManager::Instance->GetWindow(EWindowTypes::HUD_Aim)->SetVisibility(ESlateVisibility::Collapsed);
	UHUDMouseCursor* HUDMouseCursor = UWindowManager::Instance->GetWindow<UHUDMouseCursor>(EWindowTypes::HUD_MouseCursor);

	if(HUDMouseCursor)
		HUDMouseCursor->SetShowMouse();

	const auto PlayerController = AARPGDemoGameMode::Instance->GetPlayerController();
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->bShowMouseCursor = true;
	
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	PlayerController->SetMouseLocation(ViewportSize.X/2,ViewportSize.Y/2);

	UWindowManager::Instance->GetWindow(EWindowTypes::Fixed_MainWindow)->SetFocus();
}

void UControllerRegistrar::OnHideMouseCursor()
{
	UWindowManager::Instance->GetWindow(EWindowTypes::HUD_Aim)->SetVisibility(ESlateVisibility::HitTestInvisible);
	UHUDMouseCursor* HUDMouseCursor = UWindowManager::Instance->GetWindow<UHUDMouseCursor>(EWindowTypes::HUD_MouseCursor);

	if(HUDMouseCursor)
		HUDMouseCursor->SetHideMouse();

	const auto PlayerController = AARPGDemoGameMode::Instance->GetPlayerController();
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;
}
