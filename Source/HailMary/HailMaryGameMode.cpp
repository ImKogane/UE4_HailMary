// Copyright Epic Games, Inc. All Rights Reserved.

#include "HailMaryGameMode.h"
#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AHailMaryGameMode::AHailMaryGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AHailMaryGameMode::BeginPlay()
{
	//Create splitscren second player
	UGameplayStatics::CreatePlayer(GetWorld(), 1, true);
}

