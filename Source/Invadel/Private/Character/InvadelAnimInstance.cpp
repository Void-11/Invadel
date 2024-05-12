// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/InvadelAnimInstance.h"
#include "Character/InvadelCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UInvadelAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	InvadelCharacter = Cast<AInvadelCharacter>(TryGetPawnOwner());
}

void UInvadelAnimInstance::NativeUpdateAnimation(const float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (InvadelCharacter == nullptr)
	{
		InvadelCharacter = Cast<AInvadelCharacter>(TryGetPawnOwner());
	}
	if (InvadelCharacter == nullptr) return;

	FVector Velocity = InvadelCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = InvadelCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = InvadelCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
}
