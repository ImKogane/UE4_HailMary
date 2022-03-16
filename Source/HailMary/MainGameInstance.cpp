// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

#include "ToolBuilderUtil.h"
#include "Kismet/GameplayStatics.h"



void UMainGameInstance::Init()
{
	Super::Init();

	//Init variables
	TaskCount = 0;
	
	//Get all phases
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APhase::StaticClass(), FoundActors);
	for (AActor* currentActor : FoundActors)
	{
		APhase* l_currentPhase = Cast<APhase>(currentActor);
		_arrPhases.Add(l_currentPhase);

		//Initial current phase
		if( l_currentPhase->GetPhase() == 0)
		{
			_currentPhase = l_currentPhase;
		}
	}
}

void UMainGameInstance::ResetInstance()
{
	Init();
}

TArray<APhase*> UMainGameInstance::GetPlayablePhases()
{
	//TODO : Get Current Phase + Previous Phases
	//_arrPlayablePhases.Add()
	for (APhase* l_currentPhase : _arrPhases)
	{
		if( l_currentPhase->GetPhase() <= _currentPhase->GetPhase())
		{
			_arrPlayablePhases.Add(l_currentPhase);
		}
	}
	return _arrPlayablePhases;
}

