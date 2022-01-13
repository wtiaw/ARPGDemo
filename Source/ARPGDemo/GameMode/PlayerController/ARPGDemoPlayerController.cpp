// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGDemoPlayerController.h"

#include "ControllerRegistrar.h"
#include "ARPGDemo/UMG/Windows/WindowManager.h"
#include "ARPGDemo/UMG/Windows/HUD/HUDMouseCursor.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

AARPGDemoPlayerController::AARPGDemoPlayerController()
{
	
}

void AARPGDemoPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ShowMouseCursor.AddDynamic(this,&AARPGDemoPlayerController::ShowCursor);
	HideMouseCursor.AddDynamic(this,&AARPGDemoPlayerController::HideCursor);
}

void AARPGDemoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("OpenSkillWindow",IE_Pressed,UControllerRegistrar::GetInstance(),&UControllerRegistrar::OnOpenSkillWindow);
	InputComponent->BindAction("OpenMainMenu",IE_Pressed,UControllerRegistrar::GetInstance(),&UControllerRegistrar::OnOpenMenu);
	InputComponent->BindAction("ShowMouse",IE_Pressed,this,&AARPGDemoPlayerController::OnShowMouseCursor);
}

void AARPGDemoPlayerController::OnShowMouseCursor()
{
	if(ShowMouseCursor.IsBound())
	{
		ShowMouseCursor.Broadcast();
	}
}

void AARPGDemoPlayerController::OnHideMouseCursor()
{
	if(HideMouseCursor.IsBound())
	{
		HideMouseCursor.Broadcast();
	}
}

void AARPGDemoPlayerController::ShowCursor()
{
	UWindowManager::Instance->GetWindow(EWindowTypes::HUD_Aim)->SetVisibility(ESlateVisibility::Collapsed);
	UHUDMouseCursor* HUDMouseCursor = UWindowManager::Instance->GetWindow<UHUDMouseCursor>(EWindowTypes::HUD_MouseCursor);

	if(HUDMouseCursor)
		HUDMouseCursor->SetShowMouse();
	
 	SetInputMode(FInputModeUIOnly());
 	bShowMouseCursor = true;

	UWindowManager::Instance->GetWindow(EWindowTypes::Fixed_MainWindow)->SetFocus();
}

void AARPGDemoPlayerController::HideCursor()
{
	UWindowManager::Instance->GetWindow(EWindowTypes::HUD_Aim)->SetVisibility(ESlateVisibility::HitTestInvisible);
	UHUDMouseCursor* HUDMouseCursor = UWindowManager::Instance->GetWindow<UHUDMouseCursor>(EWindowTypes::HUD_MouseCursor);

	if(HUDMouseCursor)
		HUDMouseCursor->SetHideMouse();
	
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}
