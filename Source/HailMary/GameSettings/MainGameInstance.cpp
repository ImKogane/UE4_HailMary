// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

//#include "ToolBuilderUtil.h"
#include "HailMary/Characters/IA_Boss/AICharacter.h"
#include "Kismet/GameplayStatics.h"



void UMainGameInstance::Init()
{
	Super::Init();

	//Init variables
	TaskCount = 1;
	ArrayLockedPlayer.Reset();
		
	//Clear array content
	ArrayPhases.Empty(); //crash here
	
	//Get all phases
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APhase::StaticClass(), FoundActors);
	for (AActor* currentActor : FoundActors)
	{
		APhase* l_currentPhase = Cast<APhase>(currentActor);
		ArrayPhases.Add(l_currentPhase);

		//Initial current phase
		if( l_currentPhase->GetPhaseIndex() == 1)
		{
			CurrentGamePhase = l_currentPhase;
		}
	}
}

void UMainGameInstance::ResetInstance()
{
	Init();
}

void UMainGameInstance::AddLockedPlayer(AStudentCharacter* studentToAdd)
{
	ArrayLockedPlayer.Add(studentToAdd);
}

void UMainGameInstance::RemoveLockedPlayer(AStudentCharacter* studentToRem)
{
	ArrayLockedPlayer.Remove(studentToRem);
}

int UMainGameInstance::GetnbLockedPlayer()
{
	return ArrayLockedPlayer.Num();
}

void UMainGameInstance::AddTaskCount(int NewTaskCount)
{
	//Increment current phase
	TaskCount += NewTaskCount;
	//Update current phase
	if( ArrayPhases.IsValidIndex(0))
	{
		for (APhase* l_currentPhase : ArrayPhases)
		{
			if(l_currentPhase->GetPhaseIndex() == TaskCount)
			{
				CurrentGamePhase = l_currentPhase;
			}
		}
	}
}

TArray<APhase*> UMainGameInstance::GetPlayablePhases(int _bossFloor)
{

	//Get Current Phase + Previous Phases
	for (APhase* l_currentPhase : ArrayPhases)
	{
		if( l_currentPhase->GetPhaseIndex() <= CurrentGamePhase->GetPhaseIndex())
		{
			ArrayPlayablePhases.Add(l_currentPhase);
		}
	}
	return ArrayPlayablePhases;
}

