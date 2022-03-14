// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

#include "ToolBuilderUtil.h"
#include "Kismet/GameplayStatics.h"



void UMainGameInstance::Init()
{
	Super::Init();

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
			_currentPhase;
		}
	}
}

void UMainGameInstance::ResetInstance()
{
	TaskCount = 0;
}

