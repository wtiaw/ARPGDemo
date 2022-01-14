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
	 * @brief HUD主窗口
	 */
	HUD_MainWindow,

	/**
	 * @brief 准星
	 */
	HUD_Aim,

	/**
	 * @brief 显示鼠标光标
	 */
	HUD_MouseCursor,

	/**
	 * @brief 头像框以及生命值BUFF栏
	 */
	HUD_AvatarFrame,
	
	/**
	 * @brief 固定主窗口
	 */
	Fixed_MainWindow,
	
	/**
	* @brief 技能栏窗口
	*/
	Fixed_SkillBarWindow,
	
	/**
	* @brief 浮动主窗口
	*/
	Floating_MainWindow,
	
	/**
	* @brief 技能窗口
	*/
	Floating_SkillWindow,

	/**
	* @brief 背包窗口
	*/
	Floating_BackpackWindow,

	/**
	* @brief 属性窗口
	*/
	Floating_PropertyWindow,

	/**
	* @brief 主菜单窗口
	*/
	Menu_MainWindow,
};
