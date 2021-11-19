// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TaskItem_Object.h"
#include "TaskItem_Object.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleElement.h"
#include "Task_Object.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API ATask_Object : public AInteractibleElement
{
	GENERATED_BODY()

	protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Task settings")
	TArray<FString> TaskList;
	
	UPROPERTY(EditDefaultsOnly, Category="Task settings")
	int TaskMinDuration;

	UPROPERTY(EditDefaultsOnly, Category="Task settings")
	int TaskMaxDuration;
	

	UPROPERTY(VisibleInstanceOnly, Category="Task details")
	FString Task;

	UPROPERTY(VisibleAnywhere, Category="Task details")
	int TaskDuration;

	UPROPERTY(VisibleAnywhere, Category="Task details")
	int TaskProgress;

	UPROPERTY(EditDefaultsOnly, Category="Items")
	TArray<TSubclassOf<ATaskItem_Object>> AvailableItems;

	UPROPERTY(VisibleAnywhere, Category="Items")
	TSubclassOf<ATaskItem_Object> MainNeedItem;
	
	UPROPERTY(VisibleAnywhere, Category="Items")
	TSubclassOf<ATaskItem_Object> OtherNeedItem;
	
	UFUNCTION()
	void GenerateTask();


	
	
};
