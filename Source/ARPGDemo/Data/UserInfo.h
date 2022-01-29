// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserInfo.generated.h"

/**
* @brief 账号信息
*/
USTRUCT(BlueprintType)
struct FUserInfo
{
	GENERATED_BODY()

	/**
	 * @brief 密码
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FString Password;

	/**
	 * @brief 是否已经登录
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	bool bIsLogin;
};
