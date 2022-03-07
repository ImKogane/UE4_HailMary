// Fill out your copyright notice in the Description page of Project Settings.


#include "Phase.h"

// Sets default values
APhase::APhase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APhase::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void APhase::Init()
{
}

// Called every frame
void APhase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

