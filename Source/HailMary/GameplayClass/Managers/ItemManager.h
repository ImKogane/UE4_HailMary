// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleItem.h"
#include "HailMary/GameplayClass/Spawner/ItemSpawner.h"
#include "ItemManager.generated.h"

UCLASS()
class HAILMARY_API AItemManager : public AActor
{
	GENERATED_BODY()

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	TArray<AInteractibleItem*> Items;

	UPROPERTY(EditDefaultsOnly, Category="Item spawn")
	TArray<TSubclassOf<AInteractibleItem>> ItemsToSpawn;
	
	UPROPERTY(EditInstanceOnly, Category="Item spawn")
	TArray<AItemSpawner*> ItemsSpawner;

	UFUNCTION()
	void SpawnItems();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AItemManager();


};
