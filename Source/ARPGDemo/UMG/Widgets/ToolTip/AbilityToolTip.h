// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "AbilityToolTip.generated.h"

/**
 * 技能详细面板
 */
UCLASS()
class ARPGDEMO_API UAbilityToolTip : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* @brief 升级时的委托
	*/
	DECLARE_DELEGATE_OneParam(FLevelChange, int);

	FLevelChange LevelChange;

	/**
	* @brief 等级文本
	*/
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UTextBlock* Level;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	/**
	* @brief 升级后调用
	* @param NewLevel 新等级
	*/
	UFUNCTION(BlueprintCallable)
	void OnLevelChanged(int NewLevel);
	
	/**
	* @brief 更新冷却时间
	* @param NewLevel 新等级
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void OnChangeCoolDown(int NewLevel);
};
