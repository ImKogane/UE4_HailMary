// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "HailMary/GameSettings/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

AMyAIController::AMyAIController()
{
	//Initialize BehaviorTreeComponent, BlackboardComponent and the corresponding key
 
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
 
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
 
	LocationToGoKey = "LocationToGo";
	TargetKey = "Target";
	bIsHoldingPlayer = "bIsHoldingPlayer";
	bIsActivateSpeaker = "bIsActivateSpeaker";
}


/**
 * @brief Get available points for teh boss destination
 * @return List of available points for destination
 */
TArray<AActor*> AMyAIController::GetAvailablePoints()
{
	if( BotDestinationPoints.Num()>0)
	{
		BotDestinationPoints.Reset();
	}
	
	_gameInstance = Cast<UMainGameInstance>(GetGameInstance());
	if(IsValid(_gameInstance))
	{
		
		if ( _gameInstance->GetCurrentPhase())
		{
			//Create lists of needed actors
			TArray<ATask_Object*> l_arrBotTasksPoints;
			TArray<ABotTargetPoint*> l_arrBotTargetPoints;
			
			//For each Playbable phases
			TArray<APhase*> l_arrPhases = _gameInstance->GetPlayablePhases(AIChar->GetBossFloor());
			for(APhase* currentPhase : l_arrPhases)
			{
				if(IsValid(currentPhase))
				{
					//Get all the Task Points and add them to the list
					for(ATask_Object*  CurrentTasksPoint: currentPhase->GetTaskObjects())
					{
						AActor* currentActor = Cast<AActor>(CurrentTasksPoint);
						BotDestinationPoints.Add(currentActor);
					}

					//Get all the Target Points and add them to the list
					for(ABotTargetPoint*  CurrentTargetPoint: currentPhase->GetBotTargetPoints())
					{
						AActor* currentActor = Cast<AActor>(CurrentTargetPoint);
						BotDestinationPoints.Add(currentActor);
					}

				}
			}
			
		}
	}
	return BotDestinationPoints; 
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
		AIChar->SetDefaultSpeed();
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

void AMyAIController::SetIsActivateSpeaker(bool bValue)
{
	if(BehaviorComp)
	{
		BlackboardComp->SetValueAsBool(bIsActivateSpeaker, bValue);
	}
}


