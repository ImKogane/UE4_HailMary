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

	void BeginPlay() override;

	UFUNCTION() void LoseGame();
	UFUNCTION() void WinGame();
	
};



