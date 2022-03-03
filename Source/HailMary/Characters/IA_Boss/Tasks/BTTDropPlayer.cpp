// Fill out your copyright notice in the Description page of Project Settings.


#include "HailMary/Characters/IA_Boss/Tasks/BTTDropPlayer.h"

#include "HailMary/Characters/IA_Boss/MyAIController.h"

EBTNodeResult::Type UBTTDropPlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());

	if(AICon)
	{
		if(AICon->AIChar)
		{
//			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("UBTTDropPlayer::ExecuteTask"));  
			AICon->AIChar->Drop();
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
