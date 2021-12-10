// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemManager.h"
#include "GameFramework/Actor.h"
#include "HailMary/GameplayClass/Spawner/TaskSpawner.h"
#include "TaskManager.generated.h"

UCLASS()
class HAILMARY_API ATaskManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATaskManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	TArray<ATask_Object*> Tasks;
	
	UPROPERTY(EditDefaultsOnly, Category="Task spawn")
	int AreaCount;

	UPROPERTY(EditDefaultsOnly, Category="Task spawn")
	int TaskCountArea;

	UPROPERTY(EditInstanceOnly, Category="Task spawn")
	TArray<ATaskSpawner*> TaskSpawners;

	UPROPERTY(VisibleAnywhere)
	TArray<AInteractibleItem*> RemainingItems;

	TArray<AInteractibleItem*> AreaItems;

	UPROPERTY(EditInstanceOnly, Category="Other")
	AItemManager* ItemManager;

	UFUNCTION()
	void SpawnTasks();

	UFUNCTION()
	TArray<AInteractibleItem*> FindItemInArea(int area);
	
	UFUNCTION()
	void DefineTaskItems(ATask_Object* Task);

};
