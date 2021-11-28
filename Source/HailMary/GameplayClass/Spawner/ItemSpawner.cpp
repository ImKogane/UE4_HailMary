// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AInteractibleItem* AItemSpawner::SpawnItemOnPoint(TSubclassOf<AInteractibleItem> ItemToSpawn)
{
	FActorSpawnParameters Params;
	Params.Owner = this;

	FVector Loc = GetActorLocation();
	FRotator Rot = GetActorRotation();
	
	AInteractibleItem* Item = GetWorld()->SpawnActor<AInteractibleItem>(ItemToSpawn, Loc, Rot, Params);

	return Item;
	
}

