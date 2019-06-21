// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Runtime/CoreUObject/Public/Templates/SubclassOf.h"

#include "SlotHandlerObject.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class NETSPEAK_API USlotHandlerObject : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	USlotHandlerObject* GetNextStateHandler();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "States")
	TSubclassOf<USlotHandlerObject> NextState;
};
