// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProjectTyrantPlayerController.generated.h"

class AMoverCharacter;
class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class PROJECTTYRANT_API AProjectTyrantPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMoverCharacter* GetMoverCharacter() const;

protected:
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> DefaultInputMappingContext;

	void AddInputMappingContext() const;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> MoveInputAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> LookInputAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> JumpInputAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> RunInputAction;

	void BindInputActions();

	// Calls Move function on the character
	void MoveActionTriggered(const FInputActionValue& Value);

	// Calls StopMoving function on the character
	void MoveActionCompleted();

	// Calls Look function on the character
	void LookActionTriggered(const FInputActionValue& Value);

	// Calls Jump function on the character
	void JumpActionTriggered();

	// Calls StopJumping function on the character
	void JumpActionCompleted();

	// Calls StartRunning function on the character
	void RunActionStarted();

	// Calls StopRunning function on the character
	void RunActionCompleted();
};