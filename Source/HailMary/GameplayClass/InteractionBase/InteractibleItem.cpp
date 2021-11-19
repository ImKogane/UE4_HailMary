// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractibleItem.h"

// Sets default values
AInteractibleItem::AInteractibleItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractibleItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractibleItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

