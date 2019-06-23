// Fill out your copyright notice in the Description page of Project Settings.

#include "SlotActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"
#include "Net/UnrealNetwork.h"
#include <Engine/ActorChannel.h>


// Sets default values
ASlotActor::ASlotActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create slot mesh
	SlotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SlotMesh"));
	SlotMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("Material'/Game/Farming/Slots/Materials/M_SlotMaterial.M_SlotMaterial'"));
	SlotMaterial = MaterialAsset.Object;

	// Create state handler
	static ConstructorHelpers::FObjectFinder<UBlueprint> DefaultStateAsset(TEXT("Blueprint'/Game/Farming/Slots/Blueprints/BP_SoilState.BP_SoilState'"));
	DefaultState = (UClass*)DefaultStateAsset.Object->GeneratedClass;

	// Set replicate actor
	bReplicates = true;
}

void ASlotActor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASlotActor, SlotStateHandler);
}

// Called when the game starts or when spawned
void ASlotActor::BeginPlay()
{
	Super::BeginPlay();

	SlotMesh->SetMaterial(0, SlotMaterial);

	SlotStateHandler = NewObject<USlotHandlerObject>(this, *DefaultState);
	Client_InitState(SlotStateHandler);
}

// Called every frame
void ASlotActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASlotActor::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (SlotStateHandler != nullptr)
	{
		WroteSomething |= Channel->ReplicateSubobject(SlotStateHandler, *Bunch, *RepFlags);
	}

	return WroteSomething;
}

void ASlotActor::Client_InitState(USlotHandlerObject* SlotStateHandler)
{
	// Set color
	UMaterialInstanceDynamic* Material = (UMaterialInstanceDynamic*)SlotMesh->CreateAndSetMaterialInstanceDynamic(0);
	Material->SetVectorParameterValue(FName(TEXT("Color")), SlotStateHandler->GetStateColor());
}

void ASlotActor::OnRep_SlotStateHandler()
{
	Client_InitState(SlotStateHandler);
}

USlotHandlerObject* ASlotActor::GetNextState()
{
	return SlotStateHandler->GetNextStateHandler();
}

void ASlotActor::SwitchToNextState()
{
	USlotHandlerObject* NextState = SlotStateHandler->GetNextStateHandler();

	if (NextState)
	{
		SlotStateHandler = NextState;
	}

	if (Role < ROLE_Authority)
	{
		Server_SwitchToNextState();
	}
}

void ASlotActor::Server_SwitchToNextState()
{
	SwitchToNextState();
}
