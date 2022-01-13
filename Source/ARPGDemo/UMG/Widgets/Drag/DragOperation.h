// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "DragOperation.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UDragOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	/**
	* @brief 被拖拽的组件
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* DraggedWidget;

	/**
	* @brief 鼠标点击组件时的位置偏移
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D DragOffset;
};
