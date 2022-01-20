// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "AbilityToolTip.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UAbilityToolTip : public UUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE_OneParam(FLevelChange, int);

	FLevelChange LevelChange;
	
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UTextBlock* Level;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
	void OnLevelChanged(int NewLevel);
};
