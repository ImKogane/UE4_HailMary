// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HailMary/GameplayClass/TaskItem_Object.h"
#include "HailMary/GameplayClass/UsableItem_Object.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleItem.h"
#include "HailMary/GameplayClass/Spawner/ItemSpawner.h"
#include "HailMary/GameplayClass/Spawner/Task_ItemSpawner.h"
#include "HailMary/GameplayClass/Spawner/Usable_ItemSpawner.h"
#include "ItemManager.generated.h"

UCLASS()
class HAILMARY_API AItemManager : public AActor
{
	GENERATED_BODY()

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	TArray<AInteractibleItem*> UsableItems;

	UPROPERTY(VisibleAnywhere)
	TArray<AInteractibleItem*> TaskItems;

	UPROPERTY(EditDefaultsOnly, Category="Item spawn")
	int MaxUsableItems;
	
	UPROPERTY(EditDefaultsOnly, Category="Item spawn")
	TArray<TSubclassOf<AUsableItem_Object>> UsableItemsToSpawn;

	UPROPERTY(EditDefaultsOnly, Category="Item spawn")
	TArray<TSubclassOf<ATaskItem_Object>> TaskItemsToSpawn;
	

	UPROPERTY(EditInstanceOnly, Category="Manager details")
	TArray<ATask_ItemSpawner*> TaskItemsSpawners;
	
	UPROPERTY(EditInstanceOnly, Category="Manager details")
	TArray<AUsable_ItemSpawner*> UsableItemsSpawners;


	//Functions
	UFUNCTION()
	void SpawnTaskItems();

	UFUNCTION()
	void SpawnUsableItems();

public:	

	AItemManager();

	FORCEINLINE TArray<AInteractibleItem*> GetUsableItems() { return UsableItems; }
	FORCEINLINE TArray<AInteractibleItem*> GetTaskItems() { return TaskItems; }

	UFUNCTION()
		void SpawnItems();

};
