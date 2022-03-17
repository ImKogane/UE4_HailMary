// Fill out your copyright notice in the Description page of Project Settings.

#include "HailMary/GameplayClass/Managers/MerryMaker_BossManager.h"

// Sets default values
AMerryMaker_BossManager::AMerryMaker_BossManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMerryMaker_BossManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMerryMaker_BossManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMerryMaker_BossManager::AddActiveSpeaker(AE_SpeakerMM* speaker)
{
	ActivesSpeakers.Add(speaker);
	if(ActivesSpeakers.Num() == 2)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("Two speaker are on !"));
	}
}

