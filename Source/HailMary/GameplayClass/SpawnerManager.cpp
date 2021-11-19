// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerManager.h"

// Sets default values
ASpawnerManager::ASpawnerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnerManager::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnTasks();
	
}


// Called every frame
void ASpawnerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


/**
 * @brief Spawn tasks on spawner, all around the map
 */
void ASpawnerManager::SpawnTasks()
{
	int RandIndex = 0;
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

			FindSpawnerList[RandIndex]->SpawnTaskOnPoint();
			FindSpawnerList.Empty();
		}
		
	}
	
}

