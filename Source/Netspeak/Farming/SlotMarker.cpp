// Fill out your copyright notice in the Description page of Project Settings.

#include "SlotMarker.h"
#include "Components/StaticMeshComponent.h"
#include "NetspeakGameMode.h"
#include "SlotUtilities.h"
#include "Engine/World.h"
#include "SlotActor.h"

// Sets default values
ASlotMarker::ASlotMarker()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a static mesh to mark player's current/selected slot
	SlotMarker = CreateDefaultSubobject<UStaticMeshComponent>("SlotMarker");
	SlotMarker->SetupAttachment(RootComponent);

	// This is just a marker, no collision handling is needed
	SlotMarker->SetCollisionProfileName(TEXT("NoCollision"));
	SetActorEnableCollision(false);

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void ASlotMarker::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASlotMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FollowTarget)
	{
		// Snap actor location to a grid slot
		FVector CurrentTargetLocation = FollowTarget->GetActorLocation();
		FVector CurrentTargetOrientation = FollowTarget->GetActorForwardVector();

		float SlotSize = FSlotUtilities::GetSlotSize(GetWorld());
		FVector DesiredLocation = FSlotUtilities::FindClosestSlot(CurrentTargetLocation, CurrentTargetOrientation, SlotSize);

		SetActorLocation(DesiredLocation);

		// Update next action text
		ASlotActor* Slot = FSlotUtilities::GetSlotAtCoordinate(SlotMarker, FSlotUtilities::ToCoordinate(DesiredLocation, SlotSize), SlotSize);
		if (Slot == NULL)
		{
			NextAction = FText::FromString(FString("Soil"));
		}
		else
		{
			if (Slot->GetNextState())
			{
				NextAction = Slot->GetNextState()->StateText;
			}
			else
			{
				NextAction = FText();
			}
		}
	}
}

void ASlotMarker::SetFollowTarget(AActor* FollowTarget)
{
	this->FollowTarget = FollowTarget;
}