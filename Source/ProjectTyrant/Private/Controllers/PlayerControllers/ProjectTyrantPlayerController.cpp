﻿// Vladislav Semchuk, 2025

#include "Controllers/PlayerControllers/ProjectTyrantPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/MoverCharacter.h"

AMoverCharacter* AProjectTyrantPlayerController::GetMoverCharacter() const
{
	return CastChecked<AMoverCharacter>(GetPawn(), ECastCheckedType::NullAllowed);
}

void AProjectTyrantPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	AddInputMappingContext();
	BindInputActions();
}

void AProjectTyrantPlayerController::AddInputMappingContext() const
{
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (ensureAlways(IsValid(EnhancedInputSubsystem)))
	{
		EnhancedInputSubsystem->AddMappingContext(DefaultInputMappingContext, 0);
	}
}

void AProjectTyrantPlayerController::BindInputActions()
{
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	if (!ensureAlways(IsValid(EnhancedInputComponent)))
	{
		return;
	}

	if (ensureAlways(MoveInputAction))
	{
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this,
			&ThisClass::MoveActionTriggered);

		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Completed, this,
			&ThisClass::MoveActionCompleted);
	}

	if (ensureAlways(LookInputAction))
	{
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this,
			&ThisClass::LookActionTriggered);
	}

	if (ensureAlways(JumpInputAction))
	{
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this,
			&ThisClass::JumpActionTriggered);

		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed, this,
			&ThisClass::JumpActionCompleted);
	}

	if (ensureAlways(RunInputAction))
	{
		EnhancedInputComponent->BindAction(RunInputAction, ETriggerEvent::Started, this,
			&ThisClass::RunActionStarted);

		EnhancedInputComponent->BindAction(RunInputAction, ETriggerEvent::Completed, this,
			&ThisClass::RunActionCompleted);
	}
}

// ReSharper disable CppMemberFunctionMayBeConst
void AProjectTyrantPlayerController::MoveActionTriggered(const FInputActionValue& Value)
{
#if DO_ENSURE
	ensureAlways(Value.GetValueType() == EInputActionValueType::Axis3D);
#endif

	AMoverCharacter* MoverCharacter = GetMoverCharacter();

	if (ensureAlways(IsValid(MoverCharacter)))
	{
		MoverCharacter->Move(Value.Get<FVector>());
	}
}

void AProjectTyrantPlayerController::MoveActionCompleted()
{
	AMoverCharacter* MoverCharacter = GetMoverCharacter();

	if (ensureAlways(IsValid(MoverCharacter)))
	{
		MoverCharacter->StopMoving();
	}
}

void AProjectTyrantPlayerController::LookActionTriggered(const FInputActionValue& Value)
{
#if DO_ENSURE
	ensureAlways(Value.GetValueType() == EInputActionValueType::Axis2D);
#endif

	AMoverCharacter* MoverCharacter = GetMoverCharacter();

	if (ensureAlways(IsValid(MoverCharacter)))
	{
		MoverCharacter->Look(Value.Get<FVector2D>());
	}
}

void AProjectTyrantPlayerController::JumpActionTriggered()
{
	AMoverCharacter* MoverCharacter = GetMoverCharacter();

	if (ensureAlways(IsValid(MoverCharacter)))
	{
		MoverCharacter->Jump();
	}
}

void AProjectTyrantPlayerController::JumpActionCompleted()
{
	AMoverCharacter* MoverCharacter = GetMoverCharacter();

	if (ensureAlways(IsValid(MoverCharacter)))
	{
		MoverCharacter->StopJumping();
	}
}

void AProjectTyrantPlayerController::RunActionStarted()
{
	AMoverCharacter* MoverCharacter = GetMoverCharacter();

	if (ensureAlways(IsValid(MoverCharacter)))
	{
		MoverCharacter->StartRunning();
	}
}

void AProjectTyrantPlayerController::RunActionCompleted()
{
	AMoverCharacter* MoverCharacter = GetMoverCharacter();

	if (ensureAlways(IsValid(MoverCharacter)))
	{
		MoverCharacter->StopRunning();
	}
}
// ReSharper restore CppMemberFunctionMayBeConst
