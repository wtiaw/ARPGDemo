// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ARPGDemoPlayerController.generated.h"

/**
 * @brief 玩家控制器
 */
UCLASS()
class ARPGDEMO_API AARPGDemoPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AARPGDemoPlayerController();

public:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

	/**
	* @brief 当按键按下时的函数调用
	* @param Index 第几个快捷栏
	*/
	UFUNCTION(BlueprintCallable)
	void OnButtonPressed(int Index);

	/**
	* @brief 当按键松开时的函数调用
	* @param Index 第几个快捷栏
	*/
	UFUNCTION(BlueprintCallable)
	void OnButtonReleased(int Index);
};
