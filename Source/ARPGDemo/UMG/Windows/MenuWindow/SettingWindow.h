// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "SettingWindow.generated.h"

// struct Indexs
// {
// 	TArray<int> Index;
// };

class UInputSetting;
/**
 * 
 */
UCLASS()
class ARPGDEMO_API USettingWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UScrollBox* InputSettingBox;
	
	UPROPERTY(BlueprintReadWrite)
	bool bSetInputKey;

	UPROPERTY(BlueprintReadWrite)
	UInputSetting* InputSettingWidget;

private:
	FKey InputKey;

	TArray<FString> InputKeys;

	// TMap<FText, Indexs> Conflict;
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	// void CheckInput(FText BeChecked);
};
