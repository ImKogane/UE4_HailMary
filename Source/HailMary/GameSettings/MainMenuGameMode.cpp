// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"

#include "HailMary/Interface/HUD/MainMenuHUD.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	//Init the Hud
	AMainMenuHUD* _gameHud = Cast<AMainMenuHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if(IsValid(_gameHud))
	{
		_gameHud->Init();
	}
	
}
