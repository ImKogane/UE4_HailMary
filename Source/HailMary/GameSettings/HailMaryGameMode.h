// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "HailMaryGameMode.generated.h"

UCLASS(minimalapi)
class AHailMaryGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHailMaryGameMode();

	UPROPERTY(VisibleAnywhere, Category = "Player")
	TArray<AStudentCharacter*> Players;

	template<typename T>
	void FindAllActors(UWorld* World, TArray<T*>& Out);

	void BeginPlay() override;

	UFUNCTION() void LoseGame();
	UFUNCTION() void WinGame();
	
};

template<typename T>
void AHailMaryGameMode::FindAllActors(UWorld* World, TArray<T*>& Out)
{
	for (TActorIterator<T> It(World); It; ++It)
	{
		Out.Add(*It);
	}
}
