// Copyright Epic Games, Inc. All Rights Reserved.

#include "U08_FeatureGameMode.h"
#include "U08_FeaturePlayerController.h"
#include "U08_FeatureCharacter.h"
#include "UObject/ConstructorHelpers.h"

AU08_FeatureGameMode::AU08_FeatureGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AU08_FeaturePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}