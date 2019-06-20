// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "NetspeakPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "NetspeakCharacter.h"
#include "Engine/World.h"

ANetspeakPlayerController::ANetspeakPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ANetspeakPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ANetspeakPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ANetspeakPlayerController::MoveRight);
}

void ANetspeakPlayerController::MoveForward(float Val)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		MyPawn->AddMovementInput(FVector::ForwardVector, Val);
	}
}

void ANetspeakPlayerController::MoveRight(float Val)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		MyPawn->AddMovementInput(FVector::RightVector, Val);
	}
}
