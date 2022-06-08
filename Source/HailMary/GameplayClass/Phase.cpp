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
	TArray<AActor*> l_foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABotTargetPoint::StaticClass(), l_foundActors);
	for (AActor* currentActor : l_foundActors)
	{
		ABotTargetPoint* l_currentTargetPoint= Cast<ABotTargetPoint>(currentActor);
		
		//only add to the list if the id of the phase is the same
		if( l_currentTargetPoint->GetPhase() == this->GetPhaseIndex())
		{
			_arrBotTargetPoints.Add(l_currentTargetPoint);
		}
	}
	//Get all TaskObjects
	l_foundActors.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATask_Object::StaticClass(), l_foundActors);
	for (AActor* currentActor : l_foundActors)
	{
		ATask_Object* l_currentTaskObject= Cast<ATask_Object>(currentActor);
		
		//only add to the list if the id of the phase is the same
		if( l_currentTaskObject->GetPhase() == this->GetPhaseIndex())
		{
			_ArrTask_Objects.Add(l_currentTaskObject);
		}
	}
}

// Called every frame
void APhase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

