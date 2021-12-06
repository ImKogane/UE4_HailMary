// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSpawner.h"
#include "Task_ItemSpawner.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API ATask_ItemSpawner : public AItemSpawner
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditInstanceOnly, Category = "Spawner details")
	int SpawnerArea;
	
public:
	ATask_ItemSpawner();

	FORCEINLINE int GetSpawnerArea(){ return SpawnerArea; }
};
