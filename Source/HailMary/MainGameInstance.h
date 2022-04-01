// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayCycle.h"
#include "Engine/GameInstance.h"
#include "GameplayClass/Phase.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	#pragma region PublicFunctions
		FORCEINLINE UFUNCTION() APlayCycle* GetPlayCycle(){return playCycle;}
		FORCEINLINE UFUNCTION() int GetTaskCount(){return TaskCount;}
		FORCEINLINE UFUNCTION() void SetDoorIsOpen(bool State){DoorIsOpen = State;}
		FORCEINLINE UFUNCTION() void AddTaskCount(int NewTaskCount);
		FORCEINLINE UFUNCTION() void SetPlayCycle(APlayCycle* newPlayCycle){ playCycle = newPlayCycle; }
		FORCEINLINE UFUNCTION() APhase* GetCurrentPhase(){return _currentPhase;}
		UFUNCTION() TArray<APhase*> GetPlayablePhases();
		UFUNCTION() void ResetInstance();
	#pragma endregion 
	
protected:
	#pragma region ProtectedVariables
		UPROPERTY(VisibleAnywhere)
		int TaskCount;
		UPROPERTY(VisibleAnywhere)
		bool DoorIsOpen;
		UPROPERTY(VisibleAnywhere)
		APlayCycle* playCycle;
		UPROPERTY(VisibleAnywhere, Category="Phase")
		APhase* _currentPhase;
		UPROPERTY(VisibleAnywhere, Category="Phase")
		TArray<APhase*> _arrPlayablePhases;
		UPROPERTY(VisibleAnywhere, Category="Phase")
		TArray<APhase*> _arrPhases;
	#pragma 
	
	#pragma region ProtectedFunctions
		void Init() override;
	#pragma endregion 
};
