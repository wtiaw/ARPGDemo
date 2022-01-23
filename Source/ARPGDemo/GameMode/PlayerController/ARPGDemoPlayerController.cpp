// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGDemoPlayerController.h"
#include "ControllerRegistrar.h"
#include "ARPGDemo/GameMode/PlayerState/ARPGDemoPlayerState.h"
#include "ARPGDemo/SaveGame/CustomSaveGame.h"
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

	if(auto SaveGame = Cast<UCustomSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Player"),0)))
	{
		SaveGameInstance = SaveGame;

		UE_LOG(LogTemp,Warning,TEXT("%f"),SaveGameInstance->Health);
	}
	else
	{
		SaveGameInstance = Cast<UCustomSaveGame>(UGameplayStatics::CreateSaveGameObject(UCustomSaveGame::StaticClass()));
	}
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

void AARPGDemoPlayerController::OnButtonPressed(int Index)
{
	const auto QuickReleaseContainer = UWindowManager::GetInstance()->GetWindow<
		USkillBar>(EWindowTypes::Fixed_SkillBarWindow)->GetQuickReleaseContainerByIndex(Index);
	QuickReleaseContainer->SetHighLight();

	const auto PS = GetPlayerState<AARPGDemoPlayerState>();
	const auto AbilityData = PS->SkillBarAbilityDatas[Index];
	
	if (AbilityData.Ability)
	{
		PS->GetAbilitySystemComponent()->TryActivateAbilityByClass(AbilityData.Ability);
	}
}

void AARPGDemoPlayerController::OnButtonReleased(int Index)
{
	const auto QuickReleaseContainer = UWindowManager::GetInstance()->GetWindow<
		USkillBar>(EWindowTypes::Fixed_SkillBarWindow)->GetQuickReleaseContainerByIndex(Index);
	QuickReleaseContainer->HideHighLight();
}
