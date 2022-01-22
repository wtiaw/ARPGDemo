// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/UMG/Windows/MenuWindow/SettingWindow.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "InputSetting.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UInputSetting : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UWidgetSwitcher* SkillSwitch;
	/**
	 * @brief 快捷键名称
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FString QuickKeyName;

	/**
	 * @brief 快捷键显示名称
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FString KeyName;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UTextBlock* Key;
	
	UPROPERTY(BlueprintReadOnly)
	USettingWindow* Parent;

	int Index;
	
public:
	UFUNCTION(BlueprintCallable)
	void ShowKey();

	UFUNCTION(BlueprintCallable)
	void ShowCircular();

	void SetWarningText();

	void SetNormalText();
};
