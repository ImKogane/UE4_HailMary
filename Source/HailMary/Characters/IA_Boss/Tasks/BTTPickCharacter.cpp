// Fill out your copyright notice in the Description page of Project Settings.


#include "HailMary/Characters/IA_Boss/Tasks/BTTPickCharacter.h"

#include "HailMary/Characters/IA_Boss/MyAIController.h"

EBTNodeResult::Type UBTTPickCharacter::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());

	if(AICon)
	{
		if(AICon->AIChar)
		{
			AICon->AIChar->Pick();
			/*if(AICon->AIChar->bHolding)
			{
				//AICon->GetBlackboardComp()->SetValueAsBool("bCanPick", false);
				AICon->GetBlackboardComp()->ClearValue("Target");
			}*/
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
