// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FunctionLibraryInput.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UFunctionLibraryInput : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * @brief 通过[ActionName]获得对应的[Key]
	 * @param InActionName 动作名称
	 * @return 按键数组
	 */
	static TArray<FKey> GetActionKey(FName InActionName);

	/**
	 * @brief 通过[Key]获得对应的[ActionName]
	 * @param InActionKey 按键
	 * @return 动作名称
	 */
	static FName GetActionName(FKey InActionKey);

	/**
	 * @brief 通过动作名称执行对应的委托
	 * @param InActionName 动作名称
	 */
	static void ExecuteActionByActionName(FName InActionName);

	/**
	 * @brief 通过按键执行对应的委托
	 * @param InActionKey 按键
	 */
	static void ExecuteActionByKey(FKey InActionKey);
};
