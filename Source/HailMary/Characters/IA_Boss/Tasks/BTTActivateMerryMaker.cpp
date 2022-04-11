// Fill out your copyright notice in the Description page of Project Settings.


#include "HailMary/Characters/IA_Boss/Tasks/BTTActivateMerryMaker.h"
#include "HailMary/Characters/IA_Boss/MyAIController.h"
#include "HailMary/GameplayClass/Elements/E_SpeakerMM.h"

EBTNodeResult::Type UBTTActivateMerryMaker::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	
	if(AICon)
	{
		if(AICon->AIChar)
		{
			AE_SpeakerMM* MerryMakerNearest = Cast<AE_SpeakerMM>(AICon->AIChar->GetNearestMerryMaker());
			
			if(IsValid(MerryMakerNearest))
			{
				MerryMakerNearest->Interaction(AICon->AIChar);
			}
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
