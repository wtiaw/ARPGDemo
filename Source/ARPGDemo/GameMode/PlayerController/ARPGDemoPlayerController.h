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
	
	/**
	* @brief 显示光标的委托
	*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShowMouseCursorDelegate);
	
	/**
	* @brief 隐藏光标的委托
	*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHideMouseCursorDelegate);

	/**
	* @brief 显示光标时的事件
	*/
	UPROPERTY(BlueprintAssignable)
	FShowMouseCursorDelegate ShowMouseCursor;

	/**
	* @brief 隐藏光标时的事件
	*/
	UPROPERTY(BlueprintAssignable)
	FHideMouseCursorDelegate HideMouseCursor;
	
public:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

	/**
	 * @brief 打开技能菜单
	 */
	// void OpenSkillWindow();

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

	/**
	 * @brief 显示光标
	 */
	UFUNCTION()
	void ShowCursor();
	
	/**
	 * @brief 隐藏光标
	 */
	UFUNCTION()
	void HideCursor();
};
