// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UICoolDownManager.generated.h"

UCLASS()
class ARPGDEMO_API UUICoolDownManager : public UObject
{
	GENERATED_BODY()

public:
	UUICoolDownManager();

	/**
	 * @brief 单例
	 */
	static UUICoolDownManager* Instance;

private:
	TArray<FTimerHandle> CoolDownTimerHandles;
	
public:
	/**
	 * @brief 获取单例
	 * @return 单例
	 */
	UFUNCTION(BlueprintCallable)
	static UUICoolDownManager* GetInstance();
};


inline UUICoolDownManager* UUICoolDownManager::GetInstance()
{
	if (!Instance)
	{
		Instance = NewObject<UUICoolDownManager>();
		Instance->AddToRoot();
	}
	return Instance;
}
