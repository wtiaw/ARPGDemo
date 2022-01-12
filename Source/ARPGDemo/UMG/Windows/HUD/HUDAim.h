// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/UMG/Windows/BaseWindow/BaseWindow.h"
#include "Components/Image.h"
#include "HUDAim.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UHUDAim : public UBaseWindow
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UImage* FrontSight;
};
