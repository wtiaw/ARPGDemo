// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/UMG/Windows/BaseWindow/BaseWindow.h"
#include "MainWindow.generated.h"

class USkillBar;
class UCanvasPanel;

/**
 * @brief 固定主窗口
 */
UCLASS()
class ARPGDEMO_API UMainWindow : public UBaseWindow
{
	GENERATED_BODY()

public:
	/**
	 * @brief 主窗口
	 */
	UPROPERTY(Meta = (BindWidget))
	UCanvasPanel* MainPanel;

	/**
	 * @brief 技能栏
	 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	USkillBar* SkillBar;
};
