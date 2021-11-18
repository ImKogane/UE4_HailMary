// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BotTargetPoint.h"
#include "AICharacter.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API AMyAIController : public AAIController
{
	GENERATED_BODY()

	/*Behavior tree comp ref*/
	UBehaviorTreeComponent* BehaviorComp;

	/*----------Blackboard----------*/
	/*Blackboard comp ref*/
	UBlackboardComponent* BlackboardComp;

	/*Blackboard keys*/
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LocationToGoKey;
	
	/*----------Blackboard----------*/

	TArray<AActor*> BotTargetPoints;

	/*Executes right when the controller possess a Pawn*/
	virtual void OnPossess(APawn* InPawn) override;

	public:
 
	/*----------Constructeur----------*/
	AMyAIController();

	//AAICharacter* AIChar;
 
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
 
	FORCEINLINE TArray<AActor*> GetAvailableTargetPoints() { return BotTargetPoints; }
};
