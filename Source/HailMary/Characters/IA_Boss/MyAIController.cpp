// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
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
			
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABotTargetPoint::StaticClass(), BotTargetPoints);
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
