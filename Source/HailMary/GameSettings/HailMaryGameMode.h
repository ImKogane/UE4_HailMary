// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HailMaryGameMode.generated.h"

UCLASS(minimalapi)
class AHailMaryGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHailMaryGameMode();

	void BeginPlay() override;

	UFUNCTION() void LoseGame();
	UFUNCTION() void WinGame();
	
};



