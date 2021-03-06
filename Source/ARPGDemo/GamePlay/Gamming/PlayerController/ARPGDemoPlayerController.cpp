// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGDemoPlayerController.h"
#include "ControllerRegister.h"
#include "ARPGDemo/GamePlay/Gamming/PlayerState/ARPGDemoPlayerState.h"
#include "ARPGDemo/UMG/Windows/WindowManager.h"
#include "ARPGDemo/UMG/Windows/FixedWindow/Skill/QuickReleaseContainer.h"
#include "ARPGDemo/UMG/Windows/FixedWindow/Skill/SkillBar/SkillBar.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

AARPGDemoPlayerController::AARPGDemoPlayerController()
{
	
}

void AARPGDemoPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp,Warning,TEXT("Conteoller"));
}

void AARPGDemoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("OpenSkillWindow",IE_Pressed,UControllerRegister::GetInstance(),&UControllerRegister::OnOpenSkillWindow);
	InputComponent->BindAction("OpenBackpackWindow",IE_Pressed,UControllerRegister::GetInstance(),&UControllerRegister::OnOpenBackpackWindow);
	InputComponent->BindAction("OpenPropertyWindow",IE_Pressed,UControllerRegister::GetInstance(),&UControllerRegister::OnOpenPropertyWindow);
	InputComponent->BindAction("OpenMainMenu",IE_Pressed,UControllerRegister::GetInstance(),&UControllerRegister::OnOpenMenu);
	
	InputComponent->BindAction("ShowMouse",IE_Pressed,UControllerRegister::GetInstance(),&UControllerRegister::OnShowMouseCursor);
}

void AARPGDemoPlayerController::OnButtonPressed(int Index)
{
	const auto PS = GetPlayerState<AARPGDemoPlayerState>();
	const auto AbilityData = PS->SkillBarAbilityDatas[Index];

	if (AbilityData)
	{
		if (PS->GetAbilitySystemComponent()->TryActivateAbilityByClass(AbilityData))
		{
			const auto QuickReleaseContainer = UWindowManager::GetInstance()->GetWindow<
				USkillBar>(EWindowTypes::Fixed_SkillBarWindow)->GetQuickReleaseContainerByIndex(Index);
			QuickReleaseContainer->SetHighLight();
		}
	}
}

void AARPGDemoPlayerController::OnButtonReleased(int Index)
{
	const auto QuickReleaseContainer = UWindowManager::GetInstance()->GetWindow<
		USkillBar>(EWindowTypes::Fixed_SkillBarWindow)->GetQuickReleaseContainerByIndex(Index);
	QuickReleaseContainer->HideHighLight();
}
