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

	UPROPERTY(BlueprintReadOnly)
	UCustomSaveGame* SaveGameInstance;

public:
	/**
	 * @brief 获得玩家控制器
	 * @return 玩家控制器
	 */
	AARPGDemoPlayerController* GetPlayerController();
	
	virtual void BeginPlay() override;
};
