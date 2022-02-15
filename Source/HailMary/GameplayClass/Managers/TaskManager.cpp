// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskManager.h"

// Sets default values
ATaskManager::ATaskManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATaskManager::BeginPlay()
{
	Super::BeginPlay();

	
	
	if(ItemManager != nullptr)
	{
		//ItemManager->SpawnItems();
		//RemainingItems = ItemManager->GetTaskItems();
		//SpawnTasks();	
		
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Nope"));    
	}
	
}


/**
 * @brief Spawn tasks on spawner, all around the map
 */
void ATaskManager::SpawnTasks()
{
	
	int RandIndex = 0;
	ATask_Object* tempTask;
	TArray<ATaskSpawner*> FindSpawnerList;
	
	for (int i = 1; i <= AreaCount; ++i)
	{
		
		for (int j = 0; j <= TaskSpawners.Num()-1; ++j)
		{
			if(TaskSpawners[j]->GetSpawnerArea() == i)
			{
				FindSpawnerList.Add(TaskSpawners[j]);
			}
			
		}

		if(FindSpawnerList.Num() > 0)
		{
			RandIndex = FMath::RandRange(0, FindSpawnerList.Num()-1);

			
			tempTask = FindSpawnerList[RandIndex]->SpawnTaskOnPoint();
			tempTask->SetTaskArea(FindSpawnerList[RandIndex]->GetSpawnerArea());
			Tasks.Add(tempTask);
			
			DefineTaskItems(tempTask);
			
			FindSpawnerList.Empty(); //Reset the area spawner list
		}
		
	}
	
}



/**
 * @brief Defines required items for a selected task
 * @param Task Task to define required items
 */
void ATaskManager::DefineTaskItems(ATask_Object* Task)
{
	int RandIndex = 0;
	AInteractibleItem* tempItem;
	TArray<AInteractibleItem*> ItemInArea;

	if(RemainingItems.Num() > 1)
	{

		//Set main task item
		ItemInArea = FindItemInArea(Task->GetTaskArea());
		RandIndex = FMath::RandRange(0, ItemInArea.Num()-1);
		tempItem = ItemInArea[RandIndex];
		Task->SetMainItem(tempItem);
		RemainingItems.Remove(tempItem);

		//Set other task item
		ItemInArea = FindItemInArea(Task->GetTaskArea());
		RandIndex = FMath::RandRange(0, ItemInArea.Num()-1);
		tempItem = ItemInArea[RandIndex];
		Task->SetOtherItem(tempItem);
		RemainingItems.Remove(tempItem);


	}
	

	
}


/**
 * @brief Find all remaining items in selected area
 * @param area Selected area index
 * @return All item in the selected area
 */
TArray<AInteractibleItem*> ATaskManager::FindItemInArea(int area)
{
	TArray<AInteractibleItem*> ItemInArea;

	for (AInteractibleItem* item : RemainingItems)
	{
		
		ATaskItem_Object* tempItem = Cast<ATaskItem_Object>(item);
		if (tempItem != nullptr)
		{
			if(tempItem->GetTaskItemArea() <= area)
			{
				ItemInArea.Add(item);
			}
		}
	}

	return ItemInArea;
}

