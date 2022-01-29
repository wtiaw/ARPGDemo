// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllerRegister.h"
#include "ARPGDemo/GamePlay/Gamming/GameMode/ARPGDemoGameMode.h"
#include "ARPGDemo/UMG/Windows/WindowManager.h"
#include "ARPGDemo/UMG/Windows/BaseWindow/BaseWindow.h"
#include "ARPGDemo/UMG/Windows/HUD/HUDMouseCursor.h"
#include "ARPGDemo/UMG/Windows/MenuWindow/MainMenu.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UControllerRegister* UControllerRegister::Instance = nullptr;

UControllerRegister* UControllerRegister::GetInstance()
{
	if (!Instance)
	{
		Instance = NewObject<UControllerRegister>();
		Instance->AddToRoot();
	}
	return Instance;
}

void UControllerRegister::Register()
{
    OpenSkillWindowDelegate.AddDynamic(this,&UControllerRegister::OnOpenSkillWindow);
    OpenBackpackWindowDelegate.AddDynamic(this,&UControllerRegister::OnOpenBackpackWindow);
    OpenPropertyWindowDelegate.AddDynamic(this,&UControllerRegister::OnOpenPropertyWindow);
	
	OpenMenuDelegate.AddDynamic(this,&UControllerRegister::OnOpenMenu);
	
	ShowMouseCursor.AddDynamic(this,&UControllerRegister::OnShowMouseCursor);
    HideMouseCursor.AddDynamic(this,&UControllerRegister::OnHideMouseCursor);
}

void UControllerRegister::UnRegister()
{
	OpenSkillWindowDelegate.RemoveDynamic(this,&UControllerRegister::OnOpenSkillWindow);
	OpenBackpackWindowDelegate.RemoveDynamic(this,&UControllerRegister::OnOpenBackpackWindow);
	OpenPropertyWindowDelegate.RemoveDynamic(this,&UControllerRegister::OnOpenPropertyWindow);
	
	OpenMenuDelegate.RemoveDynamic(this,&UControllerRegister::OnOpenMenu);
	
	ShowMouseCursor.RemoveDynamic(this,&UControllerRegister::OnShowMouseCursor);
	HideMouseCursor.RemoveDynamic(this,&UControllerRegister::OnHideMouseCursor);
}

void UControllerRegister::OnOpenMenu()
{
	UMainMenu* MainMenu = Cast<UMainMenu>(CreateWidget(AARPGDemoGameMode::Instance->GetPlayerController(),UWindowManager::GetInstance()->MenuMainWindowClass));
	MainMenu->AddToViewport();
}

void UControllerRegister::OnOpenSkillWindow()
{
	UWindowManager::GetInstance()->OpenFloatingWindow(EWindowTypes::Floating_SkillWindow);
}

void UControllerRegister::OnOpenBackpackWindow()
{
	FVector2D Location = FVector2D::ZeroVector;
	Location.X += UWidgetLayoutLibrary::GetViewportSize(AARPGDemoGameMode::Instance).X / 4;
	
	UWindowManager::GetInstance()->OpenFloatingWindow(EWindowTypes::Floating_BackpackWindow, Location);
}

void UControllerRegister::OnOpenPropertyWindow()
{
	FVector2D Location = FVector2D::ZeroVector;
	Location.X -= UWidgetLayoutLibrary::GetViewportSize(AARPGDemoGameMode::Instance).X / 4;
	
	UWindowManager::GetInstance()->OpenFloatingWindow(EWindowTypes::Floating_PropertyWindow, Location);
}

void UControllerRegister::OnShowMouseCursor()
{
	//隐藏准星
	UWindowManager::GetInstance()->GetWindow(EWindowTypes::HUD_Aim)->SetVisibility(ESlateVisibility::Collapsed);
	UHUDMouseCursor* HUDMouseCursor = UWindowManager::GetInstance()->GetWindow<UHUDMouseCursor>(EWindowTypes::HUD_MouseCursor);

	if(HUDMouseCursor)
		HUDMouseCursor->SetShowMouse();

	const auto PlayerController = AARPGDemoGameMode::Instance->GetPlayerController();
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->bShowMouseCursor = true;
	
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	PlayerController->SetMouseLocation(ViewportSize.X/2,ViewportSize.Y/2);

	UWindowManager::GetInstance()->GetWindow(EWindowTypes::Fixed_MainWindow)->SetFocus();
}

void UControllerRegister::OnHideMouseCursor()
{
	UWindowManager::GetInstance()->GetWindow(EWindowTypes::HUD_Aim)->SetVisibility(ESlateVisibility::HitTestInvisible);
	UHUDMouseCursor* HUDMouseCursor = UWindowManager::GetInstance()->GetWindow<UHUDMouseCursor>(EWindowTypes::HUD_MouseCursor);

	if(HUDMouseCursor)
		HUDMouseCursor->SetHideMouse();

	const auto PlayerController = AARPGDemoGameMode::Instance->GetPlayerController();
	
	//防止退出时崩溃
	if(PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
	}
}
