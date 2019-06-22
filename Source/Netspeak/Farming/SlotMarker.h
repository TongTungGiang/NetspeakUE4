// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlotMarker.generated.h"

UCLASS()
class NETSPEAK_API ASlotMarker : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASlotMarker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION(BlueprintCallable)
	void SetFollowTarget(AActor* FollowTarget);

private:

	/** A square mesh showing where is the player's selected slot */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Slot, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SlotMarker;

	/** Reference to player's actor (we don't need the whole Character class anyways) */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Slot, meta = (AllowPrivateAccess = "true"))
	AActor* FollowTarget;

	/** Reference to player's actor (we don't need the whole Character class anyways) */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Slot, meta = (AllowPrivateAccess = "true"))
	FText NextAction;

};
