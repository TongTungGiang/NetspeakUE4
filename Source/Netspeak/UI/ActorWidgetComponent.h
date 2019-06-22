// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ActorWidgetComponent.generated.h"

/**
* Extension of the WidgetComponent to make it easy to have owning Actor context to the Widget. 
* Commonly used to display health bars, names, and interaction panels above Actors.
* Automatically calls SetOwningActor on the widget if the correct type of widget is used (ActorAttachWidget)
* Credit: https://www.tomlooman.com/creating-actor-widgets-umg/
*/
UCLASS(meta = (BlueprintSpawnableComponent))
class NETSPEAK_API UActorWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()	

public:

	UActorWidgetComponent();

	virtual void InitWidget() override;
};
