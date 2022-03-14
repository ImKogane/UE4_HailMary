// Fill out your copyright notice in the Description page of Project Settings.


#include "Phase.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
APhase::APhase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APhase::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void APhase::Init()
{
	//Get all BotTargetPoints
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABotTargetPoint::StaticClass(), FoundActors);
	for (AActor* currentActor : FoundActors)
	{
		ABotTargetPoint* l_currentTargetPoint= Cast<ABotTargetPoint>(currentActor);
		
		//only add to the list if the id of the phase is the same
		if( l_currentTargetPoint->GetPhase() == this->GetPhase())
		{
			_arrBotTargetPoints.Add(l_currentTargetPoint);
		}
	}
}

// Called every frame
void APhase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

