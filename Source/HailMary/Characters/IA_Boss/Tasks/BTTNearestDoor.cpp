// Fill out your copyright notice in the Description page of Project Settings.


#include "HailMary/Characters/IA_Boss/Tasks/BTTNearestDoor.h"
#include "HailMary/Characters/IA_Boss/MyAIController.h"
#include "HailMary/GameplayClass/Elements/BackDoor.h"

EBTNodeResult::Type UBTTNearestDoor::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());

	if(AICon)
	{
		if(AICon->AIChar)
		{
			ABackDoor* backDoorNearest = Cast<ABackDoor>(AICon->AIChar->GetNearestDoor());
			if(IsValid(backDoorNearest))
            {
				FVector vecLocation = backDoorNearest->GetEntrancePosition();
				AICon->GetBlackboardComp()->SetValueAsVector("LocationToGo", vecLocation );
            }
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
