// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/InvadelCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InvadelComponents/CombatComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AInvadelCharacter::AInvadelCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	FollowCamera->PostProcessSettings.bOverride_DepthOfFieldFstop = true;
	FollowCamera->PostProcessSettings.DepthOfFieldFstop = 32;
	FollowCamera->PostProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
	FollowCamera->PostProcessSettings.DepthOfFieldFocalDistance = 10000;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat Component"));
	Combat->SetIsReplicated(true);

}


void AInvadelCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultInputMapping, 0);
		}
	}
}

void AInvadelCharacter::Move(const FInputActionValue& Value)
{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FRotationMatrix RotationMatrix(YawRotation);
		// get forward vector
		const FVector ForwardDirection = RotationMatrix.GetUnitAxis(EAxis::X);

		// get right vector
		const FVector RightDirection = RotationMatrix.GetUnitAxis(EAxis::Y);

		// add movement
		const FVector2D MovementVector = Value.Get<FVector2D>();
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
}

void AInvadelCharacter::Look(const FInputActionValue& Value)
{
	if (IsValid(Controller))
	{
		// add yaw and pitch input to controller
		const FVector2D LookAxisVector = Value.Get<FVector2D>();
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}


void AInvadelCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AInvadelCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AInvadelCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AInvadelCharacter::Look);
	}


}

