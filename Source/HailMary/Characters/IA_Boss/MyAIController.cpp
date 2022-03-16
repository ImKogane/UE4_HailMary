// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

#include "HailMary/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"


AMyAIController::AMyAIController()
{
	//Initialize BehaviorTreeComponent, BlackboardComponent and the corresponding key
 
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
 
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
 
	LocationToGoKey = "LocationToGo";
	TargetKey = "Target";
	bIsHoldingPlayer = "bIsHoldingPlayer";
}

TArray<AActor*> AMyAIController::GetAvailableTargetPoints()
{
	BotTargetPoints.Reset();
	//Get BotTargetPoints of the Current and previous Phase
	_gameInstance = Cast<UMainGameInstance>(GetGameInstance());
	if(IsValid(_gameInstance))
	{
		if ( _gameInstance->GetCurrentPhase())
		{
			//Create the list of target Points
			TArray<ABotTargetPoint*> l_arrBotTargetPoints;

			//For each Playbable phases
			TArray<APhase*> l_arrPhases = _gameInstance->GetPlayablePhases();
			for(APhase* currentPhase : l_arrPhases)
			{
				//Get all the Target Points and add them to the list
				for(ABotTargetPoint*  CurrentTargetPoint: currentPhase->GetBotTargetPoints())
				{
					l_arrBotTargetPoints.Add(CurrentTargetPoint);
				}
			}
			
			//Convert the list of Target point to actors
			for (ABotTargetPoint* currentBotTargetPoint : l_arrBotTargetPoints )
			{
				AActor* currentActor = Cast<AActor>(currentBotTargetPoint);
				BotTargetPoints.Add(currentBotTargetPoint);
			}
		}
	}
	return BotTargetPoints; 
}

void AMyAIController::OnPossess(APawn* InPawn)
{
		Super::OnPossess(InPawn);
 
		//Get the possessed Character and check if it's my own AI Character
		 AIChar = Cast<AAICharacter>(InPawn);
 
		if (AIChar)
		{
			//If the blackboard is valid initialize the blackboard for the corresponding behavior tree
			if (AIChar->BehaviorTree->BlackboardAsset)
			{
				BlackboardComp->InitializeBlackboard(*(AIChar->BehaviorTree->BlackboardAsset));
			}
			
			//Start the behavior tree which corresponds to the specific character
			BehaviorComp->StartTree(*AIChar->BehaviorTree);

			//Init the defaults values of the Ai
			SetIsHoldingPlayer(false);
		}
	}

void AMyAIController::SetSeenTarget(APawn* InPawn)
{
	//Registers the Pawn that the AI has seen in the blackboard
	//AAICharacter* AIChar = Cast<AAICharacter>(InPawn);
	if (BlackboardComp)
	{
		AIChar->bAIVisible = true;
		BlackboardComp->SetValueAsObject(TargetKey, InPawn);
	}
}

void AMyAIController::SetNotSeenTarget()
{
	if(BehaviorComp)
	{
		AIChar->bAIVisible = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Je te vois pas"));
		BlackboardComp->ClearValue("Target");
	}
}

void AMyAIController::SetIsHoldingPlayer(bool bValue)
{
	if(BehaviorComp)
	{
		BlackboardComp->SetValueAsBool(bIsHoldingPlayer, bValue);
	}
}
