// Fill out your copyright notice in the Description page of Project Settings.

#include "SlotHandlerObject.h"

USlotHandlerObject* USlotHandlerObject::GetNextStateHandler()
{
	USlotHandlerObject* Instance = NewObject<USlotHandlerObject>(this, *NextState);
	return Instance;
}
