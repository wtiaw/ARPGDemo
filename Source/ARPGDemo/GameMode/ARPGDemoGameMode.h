// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerController/ARPGDemoPlayerController.h"
#include "ARPGDemoGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API AARPGDemoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AARPGDemoGameMode();
	
	static AARPGDemoGameMode* Instance;

public:
	AARPGDemoPlayerController* GetPlayerController();
	
	virtual void BeginPlay() override;
};
