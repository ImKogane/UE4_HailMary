// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_Object.h"

#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"

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
		MainNeedItemName = AvailableItems[RandIndex].GetDefaultObject()->GetItemName();
		AvailableItems.RemoveAt(RandIndex);
	
		RandIndex = FMath::RandRange(0, AvailableItems.Num()-1);
		OtherNeedItemName = AvailableItems[RandIndex].GetDefaultObject()->GetItemName();
		AvailableItems.RemoveAt(RandIndex);
	
	}

	//Define task duration
	TaskDuration = FMath::RandRange(TaskMinDuration, TaskMaxDuration);
	
	
}

/*
 
void AInteractibleItem::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
								const FHitResult& SweepResult)
{
	AStudentCharacter* Player = Cast<AStudentCharacter>(OtherActor);
	if (Player == nullptr)
	{
		//Overlap actor isn't the player
		return;
	}

	//Action
	
}

void AInteractibleItem::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AStudentCharacter* Player = Cast<AStudentCharacter>(OtherActor);
	if (Player == nullptr)
	{
		//Overlap actor isn't the player
		return;
	}

	//Action
}
*/
