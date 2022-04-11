// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskPointSelection.h"

#include "HailMary/Characters/IA_Boss/MyAIController.h"
#include "HailMary/GameplayClass/Elements/Task_Object.h"

EBTNodeResult::Type UBTTaskPointSelection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
 
	/*If the Controller is valid:
	1)Get the Blackboard Component and the Current task of the bot
	2)Search for the next task, which will be different from the Current task*/
	if (AICon)
	{
       
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
		ATask_Object* l_currentTask = Cast<ATask_Object>(BlackboardComp->GetValueAsObject("LocationToGo"));
		
		TArray<AActor*> AvailableTasksPoints = AICon->GetAvailableTasksPoints();
       
		//This variable will contain a random index in order to determine the next possible point
		int32 RandomIndex;
 
		//Here, we store the possible next target point
		ATask_Object* NextTasksPoint = nullptr;
 
		//Find a next point which is different from the current one
		if(AvailableTasksPoints.IsValidIndex(0))
		{
			if( AvailableTasksPoints.Num()>1)
			{
				do
				{
					RandomIndex = FMath::RandRange(0, AvailableTasksPoints.Num()-1);
					//Remember that the Array provided by the Controller function contains AActor* objects so we need to cast.
					NextTasksPoint = Cast<ATask_Object>(AvailableTasksPoints[RandomIndex]);
				} while (l_currentTask == NextTasksPoint);
			}
			else
			{
				RandomIndex = FMath::RandRange(0, AvailableTasksPoints.Num()-1);
				//Remember that the Array provided by the Controller function contains AActor* objects so we need to cast.
				NextTasksPoint = Cast<ATask_Object>(AvailableTasksPoints[RandomIndex]);
			}


			//Update the next location in the Blackboard so the bot can move to the next Blackboard value
			FVector vecLocation = NextTasksPoint->GetActorLocation();
			BlackboardComp->SetValueAsVector("LocationToGo", vecLocation );
			//		BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint); //Old way, move to actor instead

 
			//At this point, the task has been successfully completed
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
