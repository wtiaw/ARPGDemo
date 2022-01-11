// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickReleaseContainer.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UQuickReleaseContainer : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FString QuickKeyName;
};
