// Fill out your copyright notice in the Description page of Project Settings.

#include "NetspeakGameState.h"
#include "ConstructorHelpers.h"


ANetspeakGameState::ANetspeakGameState()
{
	SlotSize = 100;

	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Farming/Slots/Blueprints/BP_SlotActor.BP_SlotActor'"));
	if (ItemBlueprint.Object) {
		DefaultSlotActorClass= ItemBlueprint.Object->GeneratedClass;
	}
}
