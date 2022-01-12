// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGDemoPlayerController.h"

#include "ARPGDemo/UMG/Windows/WindowManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

AARPGDemoPlayerController::AARPGDemoPlayerController()
{
	
}

void AARPGDemoPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AARPGDemoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("OpenSkillWindow",IE_Pressed,this,&AARPGDemoPlayerController::OpenSkillWindow);
}

void AARPGDemoPlayerController::OpenSkillWindow()
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,TEXT("打开技能窗口"));

	UWindowManager::Instance->OpenFloatingWindow(EWindowTypes::Floating_SkillWindow);
}

void AARPGDemoPlayerController::OnShowMouseCursor()
{
	UWindowManager::Instance->GetWindow(EWindowTypes::HUD_Aim)->SetVisibility(ESlateVisibility::Collapsed);
	
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}

void AARPGDemoPlayerController::OnHideMouseCursor()
{
	UWindowManager::Instance->GetWindow(EWindowTypes::HUD_Aim)->SetVisibility(ESlateVisibility::HitTestInvisible);
	
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}
