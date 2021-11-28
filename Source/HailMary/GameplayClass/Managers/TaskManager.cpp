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
		ItemManager->SpawnItems();
		RemainingItems = ItemManager->GetItems();
		SpawnTasks();	
		
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
			Tasks.Add(tempTask);
			
			DefineTaskItems(tempTask);
			
			FindSpawnerList.Empty(); //Reset the area spawner list
		}
		
	}
	
}

void ATaskManager::DefineTaskItems(ATask_Object* Task)
{
	int RandIndex = 0;

	if(RemainingItems.Num() > 1)
	{
		RandIndex = FMath::RandRange(0, RemainingItems.Num()-1);
		Task->SetMainItem(RemainingItems[RandIndex]);
		RemainingItems.RemoveAt(RandIndex);

		RandIndex = FMath::RandRange(0, RemainingItems.Num()-1);
		Task->SetOtherItem(RemainingItems[RandIndex]);
		RemainingItems.RemoveAt(RandIndex);

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Debug"));    
	}
	

	
}

