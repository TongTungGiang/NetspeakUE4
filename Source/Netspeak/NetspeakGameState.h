// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "NetspeakGameState.generated.h"

/**
 * 
 */
UCLASS()
class NETSPEAK_API ANetspeakGameState : public AGameState
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
	float GetSlotSize() { return SlotSize; }

private:
	// Configurations
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Configuration", meta = (AllowPrivateAccess = "true"))
	float SlotSize;
	// End Configuration	
};
