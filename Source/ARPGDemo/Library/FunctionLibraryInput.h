// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FunctionLibraryInput.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UFunctionLibraryInput : public UObject
{
	GENERATED_BODY()

public:
	static TArray<FKey> GetActionKey(FName InActionName);

	static FName GetActionName(FKey InActionKey);

	static void ExecuteActionByActionName(FName InActionName);

	static void ExecuteActionByKey(FKey InActionKey);
};
