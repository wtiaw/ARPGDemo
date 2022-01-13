// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGDemoPlayerController.h"
#include "ControllerRegistrar.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

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

	InputComponent->BindAction("OpenSkillWindow",IE_Pressed,UControllerRegistrar::GetInstance(),&UControllerRegistrar::OnOpenSkillWindow);
	InputComponent->BindAction("OpenBackpackWindow",IE_Pressed,UControllerRegistrar::GetInstance(),&UControllerRegistrar::OnOpenBackpackWindow);
	InputComponent->BindAction("OpenPropertyWindow",IE_Pressed,UControllerRegistrar::GetInstance(),&UControllerRegistrar::OnOpenPropertyWindow);
	InputComponent->BindAction("OpenMainMenu",IE_Pressed,UControllerRegistrar::GetInstance(),&UControllerRegistrar::OnOpenMenu);
	
	InputComponent->BindAction("ShowMouse",IE_Pressed,UControllerRegistrar::GetInstance(),&UControllerRegistrar::OnShowMouseCursor);
}
