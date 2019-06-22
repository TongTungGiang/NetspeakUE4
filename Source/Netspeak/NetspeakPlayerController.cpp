// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "NetspeakPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "NetspeakCharacter.h"
#include "Engine/World.h"
#include "NetspeakGameMode.h"
#include "Farming/SlotUtilities.h"
#include "Farming/SlotActor.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"

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

	InputComponent->BindAction("SlotInteract", IE_Pressed, this, &ANetspeakPlayerController::InteractWithClosestSlot);
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

void ANetspeakPlayerController::InteractWithClosestSlot()
{
	APawn* const MyPawn = GetPawn();
	if (!MyPawn)
	{
		return;
	}


	UWorld* const World = GetWorld();
	if (!World)
	{
		return;
	}

	float SlotSize = FSlotUtilities::GetSlotSize(World);
	FVector ActiveSlotCoordinate = FSlotUtilities::FindClosestSlotCoordinate(MyPawn->GetActorLocation(), MyPawn->GetActorForwardVector(), SlotSize);

	// Process detected result
	ANetspeakCharacter* MyChar = (ANetspeakCharacter*)MyPawn;
	ASlotActor* SlotAtCoordinate = FSlotUtilities::GetSlotAtCoordinate(MyChar->GetSlotDetector(), ActiveSlotCoordinate, SlotSize);
	if (SlotAtCoordinate)
	{
		//SlotAtCoordinate->SwitchToNextState();
		UE_LOG(LogTemp, Log, TEXT("Switch to next state"));
		SlotAtCoordinate->SwitchToNextState();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Should create new slot at %s"), *ActiveSlotCoordinate.ToString());
		World->SpawnActor<ASlotActor>(MyChar->GetDefaultSlotActorClass(),
									  FSlotUtilities::ToWorldPosition(ActiveSlotCoordinate, SlotSize),
									  FRotator::ZeroRotator);
	}

}
