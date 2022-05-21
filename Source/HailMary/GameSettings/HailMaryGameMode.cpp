// Copyright Epic Games, Inc. All Rights Reserved.

#include "HailMaryGameMode.h"
#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AHailMaryGameMode::AHailMaryGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/Students/BP_StudentCharacterTest"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AHailMaryGameMode::BeginPlay()
{
	//Create splitscren second player
	UGameplayStatics::CreatePlayer(GetWorld(), 1, true);

	//Init the Hud
	AGameHUD* l_gameHud = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if(IsValid(l_gameHud))
	{
		l_gameHud->Init();
	}
}

void AHailMaryGameMode::LoseGame()
{
	AGameHUD* l_gameHud = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if(IsValid(l_gameHud))
	{
		UGameplayStatics::GetPlayerController(this, 0)->bShowMouseCursor = true;
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		l_gameHud->ShowLoseScreen(true);
	}
}

void AHailMaryGameMode::WinGame()
{
}

