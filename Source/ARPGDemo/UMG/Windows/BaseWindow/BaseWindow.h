// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/UMG/Windows/WindowType.h"
#include "Blueprint/UserWidget.h"
#include "BaseWindow.generated.h"


/**
 * @brief 基础窗口
 */
UCLASS()
class ARPGDEMO_API UBaseWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	UBaseWindow(const FObjectInitializer& ObjectInitializer);
	
protected:
	/**
	 * @brief 窗口类型
	 */
	UPROPERTY(EditAnywhere)
	EWindowTypes WindowType;

protected:
	/**
	 * @brief 注册窗口
	 * @param InWindowType 窗口类型
	 * @param Window 窗口指针
	 */
	void RegisterWindow(EWindowTypes InWindowType, UBaseWindow* Window);

public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	/**
	 * @brief 得到窗口类型
	 * @return 窗口类型
	 */
	EWindowTypes GetWindowType() const;
};
