// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/Data/UserInfo.h"
#include "GameFramework/SaveGame.h"
#include "UserInfoSave.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UUserInfoSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TMap<FString,FUserInfo> UserInfo;
};
