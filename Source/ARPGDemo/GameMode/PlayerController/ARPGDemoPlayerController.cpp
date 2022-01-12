// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGDemoPlayerController.h"

#include "ARPGDemo/UMG/Windows/WindowManager.h"
#include "ARPGDemo/UMG/Windows/HUD/HUDMouseCursor.h"
#include "ARPGDemo/UMG/Windows/MenuWindow/MainMenu.h"
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

	InputComponent->BindAction("OpenSkillWindow",IE_Pressed,this,&AARPGDemoPlayerController::OpenSkillWindow);
	InputComponent->BindAction("OpenMainMenu",IE_Pressed,this,&AARPGDemoPlayerController::OpenMenuWindow);
	InputComponent->BindAction("ShowMouse",IE_Pressed,this,&AARPGDemoPlayerController::OnShowMouseCursor);
}

void AARPGDemoPlayerController::OpenSkillWindow()
{
	UWindowManager::Instance->OpenFloatingWindow(EWindowTypes::Floating_SkillWindow);
}

void AARPGDemoPlayerController::OpenMenuWindow()
{
	TSubclassOf<UBaseWindow> MainMenuClass = LoadClass<UUserWidget>(
		NULL, TEXT("WidgetBlueprint'/Game/ARPGDemo/Blueprints/UMG/Windows/Menu/WBP_MainMenu.WBP_MainMenu_C'"));

	UMainMenu* MainMenu = Cast<UMainMenu>(CreateWidget(this, MainMenuClass));
	MainMenu->AddToViewport();
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
