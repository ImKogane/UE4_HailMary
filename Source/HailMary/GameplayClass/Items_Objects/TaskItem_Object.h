// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleItem.h"
#include "TaskItem_Object.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API ATaskItem_Object : public AInteractibleItem
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Items details")
	int TaskItemArea;

public:
	ATaskItem_Object();

	FORCEINLINE void SetTaskItemArea(int area){TaskItemArea = area;}
	FORCEINLINE int GetTaskItemArea(){return TaskItemArea;}

	
};
