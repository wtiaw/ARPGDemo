// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/UMG/Windows/BaseWindow/BaseWindow.h"
#include "Components/Button.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UMainMenu : public UBaseWindow
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);
	/**
	* @brief 菜单窗口关闭时的委托
	*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMenuWindowCloseDelegate);

	/**
	* @brief 菜单窗口关闭时的事件
	*/
	UPROPERTY(BlueprintAssignable)
	FMenuWindowCloseDelegate WindowClose;

	/**
	* @brief 菜单窗口打开时的委托
	*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMenuWindowOpenDelegate);

	/**
	* @brief 菜单窗口打开时的事件
	*/
	UPROPERTY(BlueprintAssignable)
	FMenuWindowCloseDelegate WindowOpen;

protected:
	/**
	* @brief 退出按钮
	*/
	UPROPERTY(Meta = (BindWidget))
	UButton* Btn_Quit;

public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;
	
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

protected:
	/**
	* @brief 退出游戏
	*/
	UFUNCTION()
	void Quit();
	
private:
    /**
     * @brief 菜单打开时调用的方法
     */
    void OnOpen();
  
    /**
     * @brief 菜单关闭时调用的方法
     */
    void OnClose();
};
