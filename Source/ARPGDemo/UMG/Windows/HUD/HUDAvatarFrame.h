// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUDHealthBar.h"
#include "ARPGDemo/UMG/Windows/BaseWindow/BaseWindow.h"
#include "HUDAvatarFrame.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UHUDAvatarFrame : public UBaseWindow
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (BindWidget))
	UHUDHealthBar* HealthBar;
};
