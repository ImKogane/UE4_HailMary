// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSelectRandomPoint.h"
#include "HailMary/Characters/IA_Boss/BotTargetPoint.h"
#include "HailMary/GameplayClass/Elements/Task_Object.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HailMary/Characters/IA_Boss/MyAIController.h"

EBTNodeResult::Type UBTSelectRandomPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	/*If the Controller is valid:
	1)Get the Blackboard Component and the Current Point of the bot
	2)Search for the next point, which will be different from the Current Point*/
	if(AICon)
	{
		
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();

		
		AActor* CurrentPoint = Cast<AActor>(BlackboardComp->GetValueAsObject("LocationToGo"));
		
		TArray<AActor*> AvailableDestinationPoints = AICon->GetAvailablePoints();
       
		//This variable will contain a random index in order to determine the next possible point
		int32 RandomIndex;
 
		//Here, we store the possible next target point
		AActor* NextDestinationPoint = nullptr;
		
		//Find a next point which is different from the current one
		if(AvailableDestinationPoints.IsValidIndex(0))
		{
			
			do
			{
				RandomIndex = FMath::RandRange(0, AvailableDestinationPoints.Num()-1);
				//Remember that the Array provided by the Controller function contains AActor* objects so we need to cast.
				NextDestinationPoint = AvailableDestinationPoints[RandomIndex];
			} while (CurrentPoint == NextDestinationPoint);

			//Update the next location in the Blackboard so the bot can move to the next Blackboard value
			FVector vecLocation = NextDestinationPoint->GetActorLocation();
			
			BlackboardComp->SetValueAsVector("LocationToGo", vecLocation );
			//		BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint); //Old way, move to actor instead

 
			//At this point, the task has been successfully completed
				
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}