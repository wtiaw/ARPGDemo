// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/UMG/Windows/BaseWindow/BaseWindow.h"
#include "Components/Image.h"
#include "HUDMouseCursor.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UHUDMouseCursor : public UBaseWindow
{
	GENERATED_BODY()

protected:
	/**
	 * @brief 显示光标 
	 */
	UPROPERTY(EditAnywhere)
	UTexture2D* ShowMouse;
	
	/**
	 * @brief 显示准星 
	 */
	UPROPERTY(EditAnywhere)
	UTexture2D* HideMouse;
	
	UPROPERTY(Meta = (BindWidget))
	UImage* Icon;

public:
	UFUNCTION()
	void SetShowMouse();

	UFUNCTION()
	void SetHideMouse();
};
