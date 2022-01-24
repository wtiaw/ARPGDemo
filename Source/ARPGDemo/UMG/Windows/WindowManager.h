// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWindow/BaseWindow.h"
#include "WindowManager.generated.h"


class UFloatingWindowBase;

/**
 * @brief 窗口管理器
 */
UCLASS()
class ARPGDEMO_API UWindowManager : public UObject
{
	GENERATED_BODY()

public:
	UWindowManager();

	/**
	 * @brief 主窗口类
	 */
	UPROPERTY()
	TSubclassOf<UBaseWindow> MainWindowClass;

	/**
	 * @brief 浮动主窗口类
	 */
	UPROPERTY()
	TSubclassOf<UBaseWindow> FloatingMainWindowClass;

	UPROPERTY()
	TSubclassOf<UBaseWindow> MenuMainWindowClass;

private:
	/**
	 * @brief 单例
	 */
	static UWindowManager* Instance;
	
	/**
	 * @brief 窗口字典
	 */
	UPROPERTY()
	TMap<EWindowTypes, UBaseWindow*> WindowMap;

	/**
	 * @brief 浮动窗口列表
	 */
	UPROPERTY()
	TArray<UFloatingWindowBase*> FloatingWindowList;
	
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
	void RegisterWindow(const EWindowTypes WindowType, UBaseWindow* Window);

	/**
	 * @brief 获取窗口
	 * @param WindowType 窗口类型
	 * @return 窗口指针（基类）
	 */
	UFUNCTION(BlueprintCallable)
	UBaseWindow* GetWindow(const EWindowTypes WindowType);

	/**
	 * @brief 注销窗口
	 * @param Window 窗口指针
	 */
	UFUNCTION(BlueprintCallable)
	void UnregisterWindow(UBaseWindow* Window);
	
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

	/**
	 * @brief 打开浮动窗口
	 * @param WindowType 窗口类型
	 * @param WindowPosition 窗口位置
	 */
	UFUNCTION(BlueprintCallable)
	void OpenFloatingWindow(const EWindowTypes WindowType, const FVector2D WindowPosition = FVector2D::ZeroVector);
	
	/**
	 * @brief 关闭浮动窗口
	 * @param WindowType 窗口类型
	 */
	UFUNCTION(BlueprintCallable)
	void CloseFloatingWindow(const EWindowTypes WindowType);

	bool ShouldHideMouseCursor();

	bool ShouldShowMouseCursor();
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
