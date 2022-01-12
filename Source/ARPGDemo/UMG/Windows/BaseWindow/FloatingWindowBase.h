// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/UMG/Windows/BaseWindow/BaseWindow.h"
#include "Components/SizeBox.h"
#include "Sound/SoundCue.h"
#include "FloatingWindowBase.generated.h"

class UCanvasPanel;
class UButton;
class UTextBlock;

/**
 * @brief 基础浮动窗口
 */
UCLASS()
class ARPGDEMO_API UFloatingWindowBase : public UBaseWindow
{
	GENERATED_BODY()

public:
	/**
	* @brief 浮动窗口打开时的委托
	*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFloatingWindowOpenDelegate);
	
	/**
	* @brief 浮动窗口关闭时的委托
	*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFloatingWindowCloseDelegate);

	/**
	* @brief 浮动窗口打开时的事件
	*/
	UPROPERTY(BlueprintAssignable)
	FFloatingWindowOpenDelegate WindowOpen;
	
	/**
	* @brief 浮动窗口关闭时的事件
	*/
	UPROPERTY(BlueprintAssignable)
	FFloatingWindowCloseDelegate WindowClosed;
	
protected:
	/**
	 * @brief 界面包裹框
	 */
	UPROPERTY(BlueprintReadOnly, Meta=(BindWidget))
	USizeBox* SizeBox;
	
	/**
	 * @brief 标题栏
	 */
	UPROPERTY(BlueprintReadOnly, Meta=(BindWidget))
	UCanvasPanel* TitleBar;

	/**
	 * @brief 标题文本
	 */
	UPROPERTY(BlueprintReadOnly, Meta=(BindWidget))
	UTextBlock* TextTitle;

	/**
	 * @brief 关闭按钮
	 */
	UPROPERTY(BlueprintReadOnly, Meta=(BindWidget))
	UButton* BtnClose;

	/**
	* @brief 是否正在拖拽
	*/
	UPROPERTY(BlueprintReadOnly)
	bool bDragging;

	/**
	 * @brief 拖拽时鼠标的像素位置
	 */
	UPROPERTY()
	FVector2D PixelPosition;

	/**
	 * @brief 拖拽时鼠标的视口位置
	 */
	UPROPERTY()
	FVector2D ViewportPosition;

	/**
	 * @brief 上一帧拖拽时鼠标的视口位置
	 */
	UPROPERTY()
	FVector2D LastMouseViewportPosition;

	/**
	 * @brief 拖拽时鼠标视口位置差值
	 */
	UPROPERTY()
	FVector2D MouseViewportPositionDelta;

	/**
	 * @brief 关闭时的音效
	 */
	UPROPERTY(EditAnywhere)
	USoundCue* CloseSoundCue;

	/**
	 * @brief 打开时的音效
	 */
	UPROPERTY(EditAnywhere)
	USoundCue* OpenSoundCue;
public:
	/**
	 * @brief 获得界面尺寸
	 * @return 界面尺寸
	 */
	FVector2D GetWindowSize() const;
	
	/**
	 * @brief 当窗口打开时触发
	 */
	UFUNCTION()
	void OnOpen();
	
	/**
	* @brief 当窗口关闭时触发
	*/
	UFUNCTION()
	void OnClose();

protected:
	virtual void NativeConstruct() override;
	
	virtual void NativeDestruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	/**
	* @brief 当窗口打开时触发
	*/
	UFUNCTION()
	virtual void OnOpenOverride();
	
	/**
	* @brief 当窗口关闭时触发
	*/
	UFUNCTION()
	virtual void OnCloseOverride();

	/**
	 * @brief 当关闭按钮点击时触发
	 */
	UFUNCTION()
	virtual void OnBtnCloseClicked();
};
