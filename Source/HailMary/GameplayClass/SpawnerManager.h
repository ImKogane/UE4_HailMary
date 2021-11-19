// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner/TaskSpawner.h"
#include "SpawnerManager.generated.h"

UCLASS()
class HAILMARY_API ASpawnerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, Category="Spawner list")
	TArray<ATaskSpawner*> TaskSpawners;

	UPROPERTY(EditDefaultsOnly)
	int AreaCount;

	UPROPERTY(EditDefaultsOnly)
	int TaskCountArea;

	UFUNCTION()
	void SpawnTasks();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
