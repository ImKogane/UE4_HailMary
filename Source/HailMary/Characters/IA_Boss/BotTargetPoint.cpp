// Fill out your copyright notice in the Description page of Project Settings.


#include "BotTargetPoint.h"

void ABotTargetPoint::BeginPlay()
{
	Super::BeginPlay();

	if( _nbPhase == -1)
	{
		//Debug
		if(GEngine)
		{
			FString txt = TEXT("ABotTargetPoint::BeginPlay() - Phase non definit");
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, txt);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(txt));
		}
	}
}
