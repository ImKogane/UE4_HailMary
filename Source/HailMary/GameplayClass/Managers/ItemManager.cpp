// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"

// Sets default values
AItemManager::AItemManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemManager::BeginPlay()
{
	Super::BeginPlay();
	
}



/**
 * @brief Spawn items on spawner, all around the map
 */
void AItemManager::SpawnItems()
{
	SpawnTaskItems();
	SpawnUsableItems();
	
	
}


/**
 * @brief Spawn usable items on specific spawner all around the level
 */
void AItemManager::SpawnUsableItems()
{
	int RandIndex = 0;
	int RandItemIndex = 0;
	AInteractibleItem* tempItem;
	int SpawnItemCount = 0;

	for (int i = 1; i < MaxUsableItems; ++i)
	{

		RandItemIndex = FMath::RandRange(0, UsableItemsToSpawn.Num()-1);
		
		RandIndex = FMath::RandRange(0, UsableItemsSpawners.Num()-1); //Choose random index in available usable items spawners indexs
		tempItem = UsableItemsSpawners[RandIndex]->SpawnItemOnPoint(UsableItemsToSpawn[RandItemIndex]); //Spawn item on the item spawner
		
		UsableItems.Add(tempItem);
		UsableItemsSpawners.RemoveAt(RandIndex);
	}
	
}

void AItemManager::SpawnTaskItems()
{
	int RandIndex = 0;
	int RandItemIndex = 0;
	AInteractibleItem* tempItem;
	TArray<ATask_ItemSpawner*> FindSpawnerList;
	
	for (int i = 1; i <= 4; ++i)
	{
		
		for (int j = 0; j <= TaskItemsSpawners.Num()-1; ++j)
		{
			if(TaskItemsSpawners[j]->GetSpawnerArea() == i)
			{
				FindSpawnerList.Add(TaskItemsSpawners[j]);
			}
			
		}


		RandItemIndex = FMath::RandRange(0, UsableItemsToSpawn.Num()-1);


		for (int k = 1; k <= 3; ++k)
		{
			if(FindSpawnerList.Num() > 0)
			{
				RandItemIndex = FMath::RandRange(0, TaskItemsToSpawn.Num()-1);
				RandIndex = FMath::RandRange(0, FindSpawnerList.Num()-1);
				
				tempItem = FindSpawnerList[RandIndex]->SpawnItemOnPoint(TaskItemsToSpawn[RandItemIndex]);

				ATaskItem_Object* taskItem = Cast<ATaskItem_Object>(tempItem);
				if (taskItem != nullptr)
				{
					taskItem->SetTaskItemArea(FindSpawnerList[RandIndex]->GetSpawnerArea());
				}
				
				TaskItems.Add(tempItem);
				
				//Clean values to next loop
				TaskItemsToSpawn.RemoveAt(RandItemIndex);
				FindSpawnerList.RemoveAt(RandIndex);

				
			}
		}
		
		FindSpawnerList.Empty();
		
		
		
	}
}




