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
	
	public:
		#pragma region PublicBVariable
	        UPROPERTY()
			AAICharacter* AIChar;
		#pragma endregion 
	
		#pragma region PublicFunctions
			/*----------Constructeur----------*/
			AMyAIController();
			/*Sets the sensed target in the blackboard*/
			UFUNCTION()
			void SetSeenTarget(APawn* InPawn);
			UFUNCTION()
			void SetNotSeenTarget();
			UFUNCTION()
			void SetIsHoldingPlayer(bool bValue);
	        UFUNCTION()
	        void SetIsActivateSpeaker(bool bValue);
	     
		#pragma endregion 

		#pragma region Accessors
			FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
			TArray<AActor*> GetAvailablePoints();
			FORCEINLINE FName GetTargetKey(){return  TargetKey;}
		#pragma endregion

	protected :
		#pragma region ProtectedFunctions
			/*Executes right when the controller possess a Pawn*/
			virtual void OnPossess(APawn* InPawn) override;
		#pragma endregion

		#pragma region ProtectedVariables
			/*Blackboard key*/
			UPROPERTY(EditDefaultsOnly, Category = AI)
			FName LocationToGoKey;
			UPROPERTY(EditDefaultsOnly, Category = AI)
			FName TargetKey ;
			UPROPERTY(EditDefaultsOnly, Category = AI)
			FName bIsHoldingPlayer;
			UPROPERTY(EditDefaultsOnly, Category = AI)
			FName bIsActivateSpeaker;
			UPROPERTY()
			TArray<AActor*> BotDestinationPoints;
			/*----------Blackboard----------*/
			/*Blackboard comp ref*/
	        UPROPERTY()
			UBlackboardComponent* BlackboardComp;
			/*Behavior tree comp ref*/
	        UPROPERTY()
			UBehaviorTreeComponent* BehaviorComp;
			UPROPERTY()
			UMainGameInstance* _gameInstance = nullptr;
		#pragma endregion 
};
