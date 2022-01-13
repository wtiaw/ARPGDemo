// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ControllerRegistrar.generated.h"

/**
 * 控制注册器，用来管理输入操作
 */
UCLASS()
class ARPGDEMO_API UControllerRegistrar : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static UControllerRegistrar* GetInstance();
	
	/**
	* @brief 打开主菜单的委托
	*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenMenuDelegate);

	/**
	* @brief 打开主菜单的事件
	*/
	UPROPERTY(BlueprintAssignable)
	FOpenMenuDelegate OpenMenuDelegate;

	/**
	* @brief 打开主菜单的委托
	*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenSkillWindowDelegate);

	/**
	* @brief 打开主菜单的事件
	*/
	UPROPERTY(BlueprintAssignable)
	FOpenSkillWindowDelegate OpenSkillWindowDelegate;

	/**
	* @brief 显示光标的委托
	*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShowMouseCursorDelegate);

	/**
	* @brief 显示光标时的事件
	*/
	UPROPERTY(BlueprintAssignable)
	FShowMouseCursorDelegate ShowMouseCursor;
	
	/**
	* @brief 隐藏光标的委托
	*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHideMouseCursorDelegate);

	/**
	* @brief 隐藏光标时的事件
	*/
	UPROPERTY(BlueprintAssignable)
	FHideMouseCursorDelegate HideMouseCursor;

private:
	static UControllerRegistrar* Instance;

public:
	/**
	 * @brief 绑定委托
	 */
	UFUNCTION(BlueprintCallable)
	void Register();

	/**
	 * @brief 打开主菜单
	 */
	UFUNCTION()
	void OnOpenMenu();

	/**
	 * @brief 打开技能菜单
	 */
	UFUNCTION()
	void OnOpenSkillWindow();

	/**
	 * @brief 显示光标
	 */
	UFUNCTION()
	void OnShowMouseCursor();
	
	/**
	 * @brief 隐藏光标
	 */
	UFUNCTION()
	void OnHideMouseCursor();
};
