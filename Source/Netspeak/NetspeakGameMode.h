// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NetspeakGameMode.generated.h"

UCLASS(minimalapi)
class ANetspeakGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANetspeakGameMode();

public:
	UFUNCTION(BlueprintCallable)
	float GetSlotSize() { return SlotSize; }

private:	
	// Configurations
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category="Configuration", meta = (AllowPrivateAccess = "true"))
	float SlotSize;
	// End Configuration
};



