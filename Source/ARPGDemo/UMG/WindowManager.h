// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WindowManager.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UWindowManager : public UObject
{
	GENERATED_BODY()

public:
	UWindowManager();

	/**
	 * @brief 单例
	 */
	static UWindowManager* Instance;

	/**
	 * @brief 主窗口类
	 */
	UPROPERTY()
	TSubclassOf<UUserWidget> MainWindowClass;

public:
	/**
	 * @brief 获取单例
	 * @return 单例
	 */
	UFUNCTION(BlueprintCallable)
	static UWindowManager* GetInstance();

	UFUNCTION(BlueprintCallable)
	void BeginPlay();
};

inline UWindowManager* UWindowManager::GetInstance()
{
	if (!Instance)
	{
		Instance = NewObject<UWindowManager>();
		Instance->AddToRoot();
	}
	return Instance;
}
