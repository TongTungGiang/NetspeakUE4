// Fill out your copyright notice in the Description page of Project Settings.

#include "SlotUtilities.h"


static const FVector AllowedDirections[] =
{
	FVector::ForwardVector,
	-FVector::ForwardVector,
	FVector::RightVector,
	-FVector::RightVector,
};



FVector FSlotUtilities::FindClosestSlot(FVector TargetPosition, FVector TargetOrientation, float SlotSize)
{
	// Convert slot coordinate to slot location
	FVector SlotCoordinate = FindClosestSlotCoordinate(TargetPosition, TargetOrientation, SlotSize);
	FVector SlotWorldLocation = ToWorldPosition(SlotCoordinate, SlotSize);

	return SlotWorldLocation;
}

FVector FSlotUtilities::FindClosestSlotCoordinate(FVector TargetPosition, FVector TargetOrientation, float SlotSize)
{
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

	FVector SlotCoordinate = ToCoordinate(TargetPosition, SlotSize);
	SlotCoordinate += DesiredDirection;

	return SlotCoordinate;
}

FVector FSlotUtilities::ToCoordinate(FVector SlotLocation, float SlotSize)
{
	int32 SlotIndexX = FMath::FloorToInt(SlotLocation.X / SlotSize);
	int32 SlotIndexY = FMath::FloorToInt(SlotLocation.Y / SlotSize);

	return FVector(SlotIndexX, SlotIndexY, 0.0f);
}

FVector FSlotUtilities::ToWorldPosition(FVector SlotCoordinate, float SlotSize)
{
	return SlotCoordinate * SlotSize + FVector(SlotSize / 2, SlotSize / 2, 0);
}
