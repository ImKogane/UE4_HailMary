// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "Kismet/GameplayStatics.h"

AMyAIController::AMyAIController()
{
	//Initialize BehaviorTreeComponent, BlackboardComponent and the corresponding key
 
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
 
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
 
	LocationToGoKey = "LocationToGo";
	BlackboardKey = "Target";
}

void AMyAIController::OnPossess(APawn* InPawn)
{
		Super::OnPossess(InPawn);
 
		//Get the possessed Character and check if it's my own AI Character
		AAICharacter* AIChar = Cast<AAICharacter>(InPawn);
 
		if (AIChar)
		{
			//If the blackboard is valid initialize the blackboard for the corresponding behavior tree
			if (AIChar->BehaviorTree->BlackboardAsset)
			{
				BlackboardComp->InitializeBlackboard(*(AIChar->BehaviorTree->BlackboardAsset));
			}
			
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABotTargetPoint::StaticClass(), BotTargetPoints);
			//Start the behavior tree which corresponds to the specific character
			BehaviorComp->StartTree(*AIChar->BehaviorTree);
		}
	}

void AMyAIController::SetSeenTarget(APawn* InPawn)
{
	//Registers the Pawn that the AI has seen in the blackboard
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(BlackboardKey, InPawn);
	}
}