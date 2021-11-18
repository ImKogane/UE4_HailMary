// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementsSpawner.h"

// Sets default values
AElementsSpawner::AElementsSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AElementsSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElementsSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

