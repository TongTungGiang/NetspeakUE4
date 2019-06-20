// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NetspeakPlayerController.generated.h"

UCLASS()
class ANetspeakPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANetspeakPlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void SetupInputComponent() override;
	// End PlayerController interface
	
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);
};


