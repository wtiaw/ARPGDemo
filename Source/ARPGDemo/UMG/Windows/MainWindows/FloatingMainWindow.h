// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/UMG/Windows/BaseWindow/BaseWindow.h"
#include "Components/CanvasPanel.h"
#include "FloatingMainWindow.generated.h"

class UFloatingWindowBase;

/**
 * @brief 浮动主窗口
 */
UCLASS()
class ARPGDEMO_API UFloatingMainWindow : public UBaseWindow
{
	GENERATED_BODY()

public:
	/**
	 * @brief 主画布
	 */
	UPROPERTY(Meta = (BindWidget))
	UCanvasPanel* Canvas;

	/**
	 * @brief 浮动窗口蓝图类
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UFloatingWindowBase>> FloatingWindows;
};
