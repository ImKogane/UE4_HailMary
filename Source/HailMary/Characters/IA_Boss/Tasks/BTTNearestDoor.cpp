// Fill out your copyright notice in the Description page of Project Settings.


#include "HailMary/Characters/IA_Boss/Tasks/BTTNearestDoor.h"

#include "HailMary/Characters/IA_Boss/MyAIController.h"

EBTNodeResult::Type UBTTNearestDoor::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());

	if(AICon)
	{
		if(AICon->AIChar)
		{
//			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("UBTTNearestDoor::ExecuteTask"));  
			AICon->AIChar->GetNearestDoor();
			if(IsValid(AICon->AIChar->NearestDoor))
            {
            	AICon->GetBlackboardComp()->SetValueAsObject("LocationToGo", AICon->AIChar->NearestDoor );
            }
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
