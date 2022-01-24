// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/Character/CharacterBase.h"
#include "ARPGDemo/UMG/Windows/HUD/HUDHealthBar.h"
#include "PlayerCharacter.generated.h"

class UGameplayAbility;
/**
 * 
 */
UCLASS()
class ARPGDEMO_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayAbility> GameplayAbility_Avoid;

	/**
	 * @brief 技能数据表
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill Item|Data")
	UDataTable* AbilityDataTable;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	FVector2D MoveAxis;
	
public:
	APlayerCharacter();

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE FVector2D GetMoveAxis() const { return MoveAxis; }
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/**
	 * @brief 视角缩放
	 */
	void Zoom(float Value);

	/**
	 * @brief 前后移动
	 */
	void MoveForward(float Value);

	/**
	 * @brief 左右移动
	 */
	void MoveRight(float Value);

	/**
	 * @brief 初始化GE
	 */
	virtual void AddStartupGameplayAbilities(int Level) override;

	/**
	 * @brief 初始化GA
	 */
	void InitAbility();
};
