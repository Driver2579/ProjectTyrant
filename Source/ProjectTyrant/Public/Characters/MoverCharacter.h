// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MoverSimulationTypes.h"
#include "Mover/ProjectTyrantMoverInputs.h"
#include "MoverCharacter.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UCharacterMoverComponent;
class UNavMoverComponent;

UCLASS(Config=Game)
class AMoverCharacter : public APawn, public IMoverInputProducerInterface
{
	GENERATED_BODY()

public:
	AMoverCharacter();

	virtual void PostLoad() override;

	virtual void BeginPlay() override;

	virtual FVector GetNavAgentLocation() const override;

	virtual void UpdateNavigationRelevance() override;

	virtual void AddMovementInput(FVector WorldDirection, float ScaleValue = 1.0f, bool bForce = false) override;

	// Should be called for looking input trigger
	void Look(const FVector2D& LookAxisVector);

	// Should be called for movement input trigger
	void Move(FVector MovementVector);

	// Should be called for movement input completion
	void StopMoving();
	
	// Should be called for run input start
	void StartRunning();

	// Should be called for run input completion
	void StopRunning();

	virtual FVector ConsumeMovementInputVector() override;

	// Returns CapsuleComponent subobject
	UCapsuleComponent* GetCapsuleComponent() const { return CapsuleComponent; }

	// Returns MeshComponent subobject
	USkeletalMeshComponent* GetMesh() const { return MeshComponent; }

#if WITH_EDITORONLY_DATA
	// Returns ArrowComponent subobject
	class UArrowComponent* GetArrowComponent() const { return ArrowComponent; }
#endif

	// Returns CameraBoomComponent subobject
	USpringArmComponent* GetCameraBoomComponent() const { return CameraBoomComponent; }

	// Returns FollowCameraComponent subobject
	UCameraComponent* GetFollowCameraComponent() const { return FollowCameraComponent; }

	// Returns CharacterMoverComponent subobject
	UCharacterMoverComponent* GetCharacterMoverComponent() const { return CharacterMoverComponent; }

	// Returns NavMoverComponent subobject
	UNavMoverComponent* GetNavMoverComponent() const { return NavMoverComponent; }

protected:
	// Whether we author our movement inputs relative to whatever base we're standing on, or leave them in world space
	UPROPERTY(BlueprintReadWrite, Category="Movement")
	bool bUseBaseRelativeMovement = true;

	// If true, rotate the Character toward the direction the actor is moving
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	bool bOrientRotationToMovement = true;

	// If true, the actor will remain vertical despite any rotation applied to the actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	bool bShouldRemainVertical = true;

	/**
	 * If true, the actor will continue orienting towards the last intended orientation (from input) even after movement
	 * intent input has ceased.
	 * This makes the character finish orienting after a quick stick flick from the player.
	 * If false, the character will not turn without an input.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bMaintainLastInputOrientation = false;

	/**
	 * Entry point for input production. Override this function in a native class to author input for the next
	 * simulation frame. Consider also calling Super method.
	 */
	virtual void ProduceInput_Implementation(int32 SimTimeMs, FMoverInputCmdContext& InputCmdResult) override;

private:
	/**
	 * The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically
	 * aligned in simple collision check functions.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	// The main skeletal mesh associated with this Character (optional sub-object). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> MeshComponent;

#if WITH_EDITORONLY_DATA
	// Component shown in the editor only to indicate character facing
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UArrowComponent> ArrowComponent;
#endif

	// Camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Camera", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USpringArmComponent> CameraBoomComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Camera", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCameraComponent> FollowCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Movement", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCharacterMoverComponent> CharacterMoverComponent;

	// Holds functionality for nav movement data and functions
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category="Components|Movement|Nav Movement",
		meta=(AllowPrivateAccess="true"))
	TObjectPtr<UNavMoverComponent> NavMoverComponent;

	// Movement input (intent or velocity) the last time we had one that wasn't zero
	FVector LastAffirmativeMoveInput = FVector::ZeroVector;

	FVector CachedMoveInputVelocity = FVector::ZeroVector;

	TSharedPtr<FProjectTyrantMoverInputs> ProducedMoverInputs = MakeShared<FProjectTyrantMoverInputs>();

	bool bRunPressed = false;
};