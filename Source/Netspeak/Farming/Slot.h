// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slot.generated.h"

/**
 * Must have BlueprintType as a specifier to have this interface exposed to blueprints
 * with this line you can easily add this interface to any blueprint class.
 *
 * https://wiki.unrealengine.com/Interfaces_in_C++
 * https://docs.unrealengine.com/en-US/Programming/UnrealArchitecture/Reference/Interfaces/index.html
 */
UINTERFACE(BlueprintType)
class NETSPEAK_API USlot : public UInterface
{
	GENERATED_BODY()

};

/**
 * Actual interface, can be derived from both BP and C++
 */
class NETSPEAK_API ISlot
{
	GENERATED_BODY()

public:

};
