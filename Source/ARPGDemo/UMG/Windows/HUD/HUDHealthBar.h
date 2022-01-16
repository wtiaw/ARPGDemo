// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "HUDHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UHUDHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (BindWidget))
	UImage* Fill;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* Health;
	
private:
	UPROPERTY()
	UMaterialInstanceDynamic* Material;

public:
	virtual void NativeConstruct() override;

	void HealthChanged();
	
protected:
	UFUNCTION(BlueprintCallable)
	void GetHealthText(FText& OutText,float& OutPercent );
};
