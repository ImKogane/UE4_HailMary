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

	SpawnItems();
	
}

// Called every frame
void AItemManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


/**
 * @brief Spawn items on spawner, all around the map
 */
void AItemManager::SpawnItems()
{
	int RandIndex = 0;
	AInteractibleItem* tempItem;

	for (TSubclassOf<AInteractibleItem> item : ItemsToSpawn)
	{
		RandIndex = FMath::RandRange(0, ItemsSpawner.Num()-1);
		tempItem = ItemsSpawner[RandIndex]->SpawnItemOnPoint(item);
		
		Items.Add(tempItem);
		ItemsSpawner.RemoveAt(RandIndex);
	}
	
	
}



