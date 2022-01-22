// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "SkillItem_Visual.generated.h"

/**
 * 技能拖拽的视觉组件
 */
UCLASS()
class ARPGDEMO_API USkillItem_Visual : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (BindWidget))
	UImage* AbilityIcon;
};
