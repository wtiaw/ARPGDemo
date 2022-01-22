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
 * 输入设置组件
 */
UCLASS()
class ARPGDEMO_API UInputSetting : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* @brief 切换Key和加载
	*/
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

	/**
	* @brief 当前的按键
	*/
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UTextBlock* Key;
	
	UPROPERTY(BlueprintReadOnly)
	USettingWindow* Parent;

	/**
	* @brief 在设置栏的下标
	*/
	int Index;
	
public:
	/**
	* @brief 显示当前的按键
	*/
	UFUNCTION(BlueprintCallable)
	void ShowKey();

	/**
	* @brief 显示加载图标
	*/
	UFUNCTION(BlueprintCallable)
	void ShowCircular();

	void SetWarningText();

	void SetNormalText();
};
