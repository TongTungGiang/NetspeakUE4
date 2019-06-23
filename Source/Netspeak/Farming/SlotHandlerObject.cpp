// Fill out your copyright notice in the Description page of Project Settings.

#include "SlotHandlerObject.h"
#include "Engine/World.h"

USlotHandlerObject* USlotHandlerObject::GetNextStateHandler()
{
	if (!NextState)
		return NULL;

	USlotHandlerObject* Instance = NewObject<USlotHandlerObject>(this, *NextState);
	return Instance;
}

UWorld* USlotHandlerObject::GetWorld() const
{
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		return nullptr;
	}
	return GetOuter() ? GetOuter()->GetWorld() : nullptr;
}
