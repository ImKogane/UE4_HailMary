// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	int TaskCount;
	
	UPROPERTY(VisibleAnywhere)
	bool DoorIsOpen;

	void ResetInstance();

public:
	FORCEINLINE int GetTaskCount(){return TaskCount;}
	
	FORCEINLINE void SetDoorIsOpen(bool State){DoorIsOpen = State;}
	FORCEINLINE void AddTaskCount(int NewTaskCount){ TaskCount += NewTaskCount; }
	
};
