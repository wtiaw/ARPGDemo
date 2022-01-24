// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/GamePlayAbilitySystem/GameplayAbility/GA/GameplayAbility_Base.h"
#include "Engine/Datatable.h"
#include "AbilityData.generated.h"

/**
 * @brief 技能类型
 */
UENUM(BluePrintType)
enum class EAbilityType : uint8
{
	/**
	 * @brief 无
	 */
	None,

	/**
	 * @brief 主动技能
	 */
	Positive,

	/**
	 * @brief 被动技能
	 */
	Passive,
};

/**
 * @brief 技能伤害类型
 */
UENUM(BluePrintType)
enum class EDamageType : uint8
{
	/**
	* @brief 无
	*/
	None,

	/**
	* @brief 物理伤害
	*/
	Physical,

	/**
	* @brief 魔法伤害
	*/
	Magic,
};

/**
* @brief 技能属性类型
*/
UENUM(BluePrintType)
enum class EElementalDamageType : uint8
{
	/**
	* @brief 无属性
	*/
	None,

	/**
	* @brief 火属性
	*/
	Fire,

	/**
	* @brief 冰属性
	*/
	Ice,

	/**
	* @brief 水属性
	*/
	Water,

	/**
	* @brief 毒属性
	*/
	Toxic,

	/**
	* @brief 电属性
	*/
	Electrical,

	/**
	* @brief 光属性
	*/
	Light,
	
	/**
	* @brief 暗属性
	*/
	Dark,
};

/**
* @brief 技能数据
*/
USTRUCT(BlueprintType)
struct FPreconditionData : public FTableRowBase
{
	GENERATED_BODY()

	/**
	 * @brief 角色等级
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	int Level;

	/**
	 * @brief 技能ID和等级映射表
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TMap<int,int> Ability;
};

/**
* @brief 技能数据
*/
USTRUCT(BlueprintType)
struct FAbilityData : public FTableRowBase
{
	GENERATED_BODY()

	/**
	 * @brief 技能ID
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	int AbilityId;
	
	/**
	 * @brief 技能名称
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FString AbilityName;

	/**
	 * @brief 当前技能等级
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	int Level;
	
	/**
	 * @brief 最小技能等级
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	int MinLevel;
	
	/**
	 * @brief 最大技能等级
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	int MaxLevel;
	
	/**
	 * @brief 伤害类型（物理/魔法）
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	EDamageType DamageType;
	
	/**
	 * @brief 元素类型
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	EElementalDamageType ElementalDamage;

	/**
	 * @brief 技能描述
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FString AbilityDescription;

	/**
	 * @brief 激活时的技能图标
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UTexture2D* ActivatedIcon;

	/**
	 * @brief 未激活时的技能图标
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UTexture2D* InactivatedAbilityIcon;
	
	/**
	 * @brief 技能种类
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	EAbilityType AbilityType;
	
	/**
	 * @brief GA类
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TSubclassOf<UGameplayAbility_Base> Ability;

	/**
	 * @brief GAS CoolDown标签
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FGameplayTagContainer Tag;

	/**
	 * @brief 冷却时间
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UCurveTable* CoolDown;

	/**
	 * @brief 前置条件
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UDataTable* Precondition;

	FAbilityData();

	FAbilityData(FString AbilityName, FString AbilityDescription, UTexture2D* ActivatedAbilityIcon, UTexture2D* InactivatedAbilityIcon,
					EAbilityType AbilityType, int Level, int MaxLevel, int MinLevel, EDamageType DamageType, EElementalDamageType ElementalDamage ,
					TSubclassOf<UGameplayAbility_Base> Ability, FGameplayTagContainer Tag, UCurveTable* CoolDown, UDataTable* Precondition);

	bool IsValid();
};
