// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class NETSPEAK_API FSlotUtilities
{

public:

	/** Find the closest slot in front of player actor, in world location */
	static FVector FindClosestSlot(FVector TargetPosition, FVector TargetOrientation, float SlotSize);

	/** Find the closest slot in front of player actor, in grid coordinate */
	static FVector FindClosestSlotCoordinate(FVector TargetPosition, FVector TargetOrientation, float SlotSize);


	static FVector ToCoordinate(FVector SlotLocation, float SlotSize);
	static FVector ToWorldPosition(FVector SlotCoordinate, float SlotSize);

	static class ASlotActor* GetSlotAtCoordinate(class UPrimitiveComponent* Detector, FVector SelectedCoordinate, float SlotSize);

	static float GetSlotSize(class UWorld* World);

	static UClass* GetDefaultSlotActorClass(UWorld* World);
};
