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

	UPROPERTY(BlueprintReadWrite)
	bool bIsAvoid = false;

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

	void Zoom(float Value);
	
	void MoveForward(float Value);
	
	void MoveRight(float Value);

	virtual void AddStartupGameplayAbilities(int Level) override;
};
