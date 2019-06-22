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

	ANetspeakGameMode* GameMode = (ANetspeakGameMode*)(World->GetAuthGameMode());
	float SlotSize = GameMode->GetSlotSize();
	FVector ActiveSlotCoordinate = FSlotUtilities::FindClosestSlotCoordinate(MyPawn->GetActorLocation(), MyPawn->GetActorForwardVector(), SlotSize);

	// Use the detector to find available slots
	TArray<AActor*> OverlappingActors;
	ANetspeakCharacter* MyChar = (ANetspeakCharacter*)MyPawn;
	MyChar->GetSlotDetector()->GetOverlappingActors(OverlappingActors, TSubclassOf<ASlotActor>());
	
	// Check if the detector found any slot with the desired coordinate
	ASlotActor* SlotAtCoordinate = NULL;
	for (auto It = OverlappingActors.CreateConstIterator(); It; ++It)
	{
		ASlotActor* CurrentSlot = (ASlotActor*)(*It);
		FVector CurrentSlotCoordinate = FSlotUtilities::ToCoordinate(CurrentSlot->GetActorLocation(), SlotSize);
		if (CurrentSlotCoordinate == ActiveSlotCoordinate)
		{
			SlotAtCoordinate = CurrentSlot;
			break;
		}
	}

	// Process detected result
	if (SlotAtCoordinate)
	{
		//SlotAtCoordinate->SwitchToNextState();
		UE_LOG(LogTemp, Log, TEXT("Switch to next state"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Should create new slot at %s"), *ActiveSlotCoordinate.ToString());
		World->SpawnActor<ASlotActor>(MyChar->GetDefaultSlotActorClass(),
									  FSlotUtilities::ToWorldPosition(ActiveSlotCoordinate, SlotSize),
									  FRotator::ZeroRotator);
	}

}
