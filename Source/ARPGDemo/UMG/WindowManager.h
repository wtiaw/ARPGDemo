// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WindowType.h"
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

private:
	/**
	 * @brief 窗口字典
	 */
	UPROPERTY()
	TMap<EWindowTypes, UUserWidget*> WindowMap;

	/**
	 * @brief 正在活跃的窗口
	 */
	TArray<UUserWidget*> ActiveWindows;
public:
	/**
	 * @brief 获取单例
	 * @return 单例
	 */
	UFUNCTION(BlueprintCallable)
	static UWindowManager* GetInstance();

	UFUNCTION(BlueprintCallable)
	void BeginPlay();

	/**
	 * @brief 注册窗口
	 * @param WindowType 窗口类型
	 * @param Window 窗口指针
	 */
	UFUNCTION(BlueprintCallable)
	void RegisterWindow(const EWindowTypes WindowType, UUserWidget* Window);

	/**
	 * @brief 获取窗口
	 * @param WindowType 窗口类型
	 * @return 窗口指针（基类）
	 */
	UFUNCTION(BlueprintCallable)
	UUserWidget* GetWindow(const EWindowTypes WindowType);

	/**
	 * @brief 获取窗口
	 * @tparam WindowT 窗口泛型
	 * @param WindowType 窗口类型
	 * @return 窗口指针
	 */
	template <typename WindowT = UUserWidget>
	WindowT* GetWindow(const EWindowTypes WindowType)
	{
		UBaseWindow* Window = GetWindow(WindowType);
		if (Window)
			return Cast<WindowT>(Window);

		return nullptr;
	}
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
