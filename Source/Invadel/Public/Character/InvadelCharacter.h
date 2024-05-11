// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InvadelCharacter.generated.h"

class UCameraComponent;
class UInputAction;
class USpringArmComponent;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class INVADEL_API AInvadelCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AInvadelCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

private:

	// Third Person Camera
	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom { nullptr };

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera { nullptr };

	//------------------------------------------------------------------------------------------------------------------

	// User Input
	
	UPROPERTY(EditDefaultsOnly, Category = "Character Input", meta = (AllowPrivateAccess = "true", RuleRangerRequired))
	TObjectPtr<UInputMappingContext> DefaultInputMapping { nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Character Input", meta = (AllowPrivateAccess = "true", RuleRangerRequired))
	TObjectPtr<UInputAction> MoveAction { nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Character Input", meta = (AllowPrivateAccess = "true", RuleRangerRequired))
	TObjectPtr<UInputAction> LookAction { nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Character Input", meta = (AllowPrivateAccess = "true", RuleRangerRequired))
	TObjectPtr<UInputAction> JumpAction { nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Character Input", meta = (AllowPrivateAccess = "true", RuleRangerRequired))
	TObjectPtr<UInputAction> CrouchAction { nullptr };
	
	//------------------------------------------------------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere)
	class UCombatComponent* Combat;
};
