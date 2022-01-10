// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/Character/CharacterBase.h"
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
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE FVector2D GetMoveAxis() const { return MoveAxis; }
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	void Zoom(float Value);
	
	void MoveForward(float Value);
	
	void MoveRight(float Value);
};
