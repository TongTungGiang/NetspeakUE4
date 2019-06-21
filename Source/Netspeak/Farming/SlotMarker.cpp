// Fill out your copyright notice in the Description page of Project Settings.

#include "SlotMarker.h"
#include "Components/StaticMeshComponent.h"


static const FVector AllowedDirections[] =
{
	FVector::ForwardVector,
	-FVector::ForwardVector,
	FVector::RightVector,
	-FVector::RightVector,
};


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
		FVector CurrentTargetLocation = FollowTarget->GetActorLocation();
		FVector CurrentTargetOrientation = FollowTarget->GetActorForwardVector();
		FVector DesiredLocation = FindClosestSlot(CurrentTargetLocation, CurrentTargetOrientation);

		SetActorLocation(DesiredLocation);
	}
}

void ASlotMarker::SetFollowTarget(AActor* FollowTarget)
{
	this->FollowTarget = FollowTarget;
}

FVector ASlotMarker::FindClosestSlot(FVector TargetPosition, FVector TargetOrientation)
{
	int SlotIndexX = TargetPosition.X / SlotSize;
	int SlotIndexY = TargetPosition.Y / SlotSize;

	// Find the closest allowed direction to current forward direction
	FVector DesiredDirection;
	float MaxDotProduct = TNumericLimits<float>::Min();
	for (auto Direction : AllowedDirections)
	{
		float Dot = FVector::DotProduct(TargetOrientation, Direction);
		if (Dot > MaxDotProduct)
		{
			DesiredDirection = Direction;
			MaxDotProduct = Dot;
		}
	}

	// Get the slot's coordinate
	FVector SlotCoordinate = FVector(SlotIndexX, SlotIndexY, 0.0f);
	SlotCoordinate += DesiredDirection;

	FVector SlotWorldLocation = SlotCoordinate * SlotSize + FVector(SlotSize / 2, SlotSize / 2, 0);

	return SlotWorldLocation;
}

