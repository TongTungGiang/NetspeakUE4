// Fill out your copyright notice in the Description page of Project Settings.

#include "SlotMarker.h"


// Sets default values
ASlotMarker::ASlotMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create a static mesh to mark player's current/selected slot
	SlotMarker = CreateDefaultSubobject<UStaticMeshComponent>("SlotMarker");
	SlotMarker->SetupAttachment(RootComponent);

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void ASlotMarker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlotMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Target)
		SetActorLocation(Target->GetActorLocation());
}

void ASlotMarker::SetTarget(AActor* Target)
{
	this->Target = Target;
}

