// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_Object.h"

void ATask_Object::BeginPlay()
{
	Super::BeginPlay();

	GenerateTask();
}

void ATask_Object::GenerateTask()
{
	int RandIndex = FMath::RandRange(0, TaskList. Num()-1);
	Task = TaskList[RandIndex];
	
	//Generate random task items
	if(AvailableItems.Num() > 0)
	{
		RandIndex = FMath::RandRange(0, AvailableItems.Num()-1);
		MainNeedItem = AvailableItems[RandIndex];
		AvailableItems.RemoveAt(RandIndex);
	
		RandIndex = FMath::RandRange(0, AvailableItems.Num()-1);
		OtherNeedItem = AvailableItems[RandIndex];
	
	}
	
	
}
