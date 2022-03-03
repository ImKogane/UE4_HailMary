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
//		    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("UBTTPickCharacter::ExecuteTask"));  
			AICon->AIChar->Pick();
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
