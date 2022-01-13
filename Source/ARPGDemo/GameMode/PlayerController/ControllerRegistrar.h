// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ControllerRegistrar.generated.h"

/**
 * 
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

private:
	static UControllerRegistrar* Instance;

public:
	UFUNCTION(BlueprintCallable)
	void Register();
	
	UFUNCTION()
	void OnOpenMenu();

	UFUNCTION()
	void OnOpenSkillWindow();
};
