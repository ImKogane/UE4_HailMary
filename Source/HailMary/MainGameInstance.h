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
		FORCEINLINE APlayCycle* GetPlayCycle(){return playCycle;}
		FORCEINLINE int GetTaskCount(){return TaskCount;}
		FORCEINLINE void SetDoorIsOpen(bool State){DoorIsOpen = State;}
		FORCEINLINE void AddTaskCount(int NewTaskCount){ TaskCount += NewTaskCount; }
		FORCEINLINE void SetPlayCycle(APlayCycle* newPlayCycle){ playCycle = newPlayCycle; }
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
		TArray<APhase*> _arrPhases;
	#pragma 
	
	#pragma region ProtectedFunctions
		void Init() override;
	#pragma endregion 
};
