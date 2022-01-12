// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelWidget.h"
#include "FunctionLibraryWidget.generated.h"

/**
 * UMG的Widget扩展函数库
 */
UCLASS()
class ARPGDEMO_API UFunctionLibraryWidget : public UObject
{
	GENERATED_BODY()

public:
	/**
	* @brief 获取目标位置处的UI组件
	*/
	UFUNCTION(BlueprintCallable)
	static UWidget* GetHoveredWidget(UPanelWidget* UIParent, FVector2D Position);
};

