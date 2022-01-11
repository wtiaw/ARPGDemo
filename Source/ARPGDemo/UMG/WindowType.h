// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "WindowType.generated.h"

/**
 * 窗口类型
 */
UENUM(BlueprintType)
enum class EWindowTypes : uint8
{
	/**
	 * @brief 无
	 */
	None,

	/**
	 * @brief 主窗口
	 */
	MainWindow,

	/**
	* @brief 浮动主窗口
	*/
	FloatingMainWindow,

	/**
	* @brief 技能栏窗口
	*/
	SkillBarWindow,

	/**
	* @brief 技能窗口
	*/
	SkillWindow,
};
