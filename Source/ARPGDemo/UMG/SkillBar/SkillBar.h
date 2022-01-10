// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "SkillBar.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API USkillBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (BindWidget))
	UHorizontalBox* EffectedAbilityBar;
};
