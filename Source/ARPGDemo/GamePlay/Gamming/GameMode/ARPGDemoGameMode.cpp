// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGDemoGameMode.h"

#include "ARPGDemo/SaveGame/CustomSaveGame.h"
#include "Kismet/GameplayStatics.h"

AARPGDemoGameMode* AARPGDemoGameMode::Instance = nullptr;

AARPGDemoGameMode::AARPGDemoGameMode()
{
	Instance = this;
}

AARPGDemoPlayerController* AARPGDemoGameMode::GetPlayerController()
{
	return Cast<AARPGDemoPlayerController>(UGameplayStatics::GetPlayerController(this, 0));;
}

void AARPGDemoGameMode::BeginPlay()
{
	Super::BeginPlay();

	if(auto SaveGame = Cast<UCustomSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Player"),0)))
	{
		SaveGameInstance = SaveGame;

		GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Red,TEXT("Load Success"));
	}
	else
	{
		SaveGameInstance = Cast<UCustomSaveGame>(UGameplayStatics::CreateSaveGameObject(UCustomSaveGame::StaticClass()));
		GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Red,TEXT("Create Success"));
	}
}
