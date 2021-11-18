// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayCycle.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayCycle::APlayCycle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayCycle::BeginPlay()
{
	Super::BeginPlay();
	LoopTime = 10;
	GetWorldTimerManager().SetTimer(GameTimer, this, &APlayCycle::Clock, 1.0f, true);
}

// Called every frame
void APlayCycle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Loop();
}

void APlayCycle::Loop()
{	
	if (LoopTime <= 0)
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
	}
}

void APlayCycle::Clock()
{
	if (LoopTime > 0)
	{
		LoopTime--;
	}
	else
	{
		GetWorldTimerManager().ClearTimer(GameTimer);
	}
}

void APlayCycle::TimerConversion()
{
	int TimeSeconds = LoopTime;
	int TimeMinuts = LoopTime / 60;
	FString Time;
}

