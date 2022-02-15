// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_Object.h"

#include "HailMary/HailMaryGameMode.h"
#include "HailMary/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ATask_Object::BeginPlay()
{
	Super::BeginPlay();

	GenerateTask();

	TheGameInstance = Cast<UMainGameInstance>(GetGameInstance());
}

void ATask_Object::GenerateTask()
{
	int RandIndex = FMath::RandRange(0, TaskList. Num()-1);
	Task = TaskList[RandIndex];

	ElementName = Task;
}



void ATask_Object::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                     const FHitResult& SweepResult)
{
	Super::OnBoxOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AStudentCharacter* Player = Cast<AStudentCharacter>(OtherActor);
	if (Player == nullptr)
	{
		return; //Overlap actor isn't the player
	}
	
	NearPlayers.Add(Player);
	
	if(MainNeedItemName != nullptr && Player->GetItemInInventory() == MainNeedItemName)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Main item good"));
		MainNeedItemName = nullptr;
		Player->ResetInventory();
	}

	if(OtherNeedItemName != nullptr && Player->GetItemInInventory() == OtherNeedItemName)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Other item good"));
		OtherNeedItemName = nullptr;
		Player->ResetInventory();
	}

	if(MainNeedItemName == nullptr && OtherNeedItemName == nullptr && !TaskUnlocked)
	{
		UnlockTask();
	}
}

void ATask_Object::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnBoxOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	AStudentCharacter* Player = Cast<AStudentCharacter>(OtherActor);
	if (Player == nullptr)
	{
		return; //Overlap actor isn't the player
	}
	NearPlayers.Remove(Player);
}

void ATask_Object::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(TaskUnlocked && !TaskCompleted)
	{
		for (AStudentCharacter* Player : NearPlayers)
		{
			if(Player->GetIsDoAction() && ElementProgress <= ElementMaxProgress)
			{
				ElementProgress += Player->GetMakeTaskSpeed();
				FString ProgressString = FString::FromInt(ElementProgress);
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, ProgressString);

				ElementInteractionCount++;
			}
			else if(ElementProgress > ElementMaxProgress)
			{
				CompleteTask();
			}
		}

		if(ElementInteractionCount == 0)
		{
			ElementProgress = 0;
		}
		
		ElementInteractionCount = 0;

	}	
}


/**
 * @brief Unlock the task if the 2 needed items are completed
 */
void ATask_Object::UnlockTask()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Task unlock"));
	TaskUnlocked = true;
}

/**
 * @brief Complete the task if the task is unlocked and the progress reach 100 percent
 */
void ATask_Object::CompleteTask()
{
	TaskCompleted = true;
	TheGameInstance->AddTaskCount(1);
	TheGameInstance->GetPlayCycle()->ResetTimer();
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Task completed"));
}