// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Skill/SkillBar/SkillBar.h"
#include "MainWindow.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UMainWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (BindWidget))
	UCanvasPanel* MainPanel;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	USkillBar* SkillBar;

public:
	virtual void NativeConstruct() override;
	
	USkillBar* GetSkillBar();
};
