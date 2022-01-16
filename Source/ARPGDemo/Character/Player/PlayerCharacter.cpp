// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "ARPGDemo/Data/Enum/EGASAbilityInputID.h"
#include "ARPGDemo/GameMode/ARPGDemoGameMode.h"
#include "ARPGDemo/GameMode/PlayerState/ARPGDemoPlayerState.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f; 
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Zoom", this, &APlayerCharacter::Zoom);

	if(GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->BindAbilityActivationToInputComponent(PlayerInputComponent,
			FGameplayAbilityInputBinds(
				FString(),
				FString(),
				FString(TEXT("EGASAbilityInputID")),
				static_cast<int32>(EGASAbilityInputID::None),
				static_cast<int32>(EGASAbilityInputID::None)
				)
		);
	}
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	const auto PS = GetPlayerState<AARPGDemoPlayerState>();

	if(PS)
	{
		AbilitySystemComponent = PS->AbilitySystemComponent;
		
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

		AbilitySetBase = PS->GetAttributeSetBase();

		AddStartupGameplayAbilities();
		
		GetAbilitySystemComponent()->GiveAbility(
			FGameplayAbilitySpec(GameplayAbility_Avoid, 1, static_cast<int32>(EGASAbilityInputID::Avoid),this));
	}
}

void APlayerCharacter::Zoom(float Value)
{
	GetCameraBoom()->TargetArmLength = FMath::Clamp<float>(GetCameraBoom()->TargetArmLength + Value, 200, 800);
}

void APlayerCharacter::MoveForward(float Value)
{
	MoveAxis.X = Value;
	
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	MoveAxis.Y = Value;
	
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
