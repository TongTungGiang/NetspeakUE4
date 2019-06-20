// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "NetspeakGameMode.h"
#include "NetspeakPlayerController.h"
#include "NetspeakCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANetspeakGameMode::ANetspeakGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ANetspeakPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}