// Fill out your copyright notice in the Description page of Project Settings.

#include "SlotHandlerObject.h"

USlotHandlerObject* USlotHandlerObject::GetNextStateHandler()
{
	if (!NextState)
		return NULL;

	USlotHandlerObject* Instance = NewObject<USlotHandlerObject>(this, *NextState);
	return Instance;
}
