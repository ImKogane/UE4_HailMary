// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskSpawner.h"
#include "HailMary/GameplayClass/Elements/Task_Object.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATaskSpawner::ATaskSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATaskSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ATaskSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ATask_Object* ATaskSpawner::SpawnTaskOnPoint()
{
	FActorSpawnParameters Params;
	Params.Owner = this;

	FVector Loc = GetActorLocation();
	FRotator Rot = GetActorRotation();
	
	ATask_Object* Task = GetWorld()->SpawnActor<ATask_Object>(TaskObject, Loc, Rot, Params);

	return Task;
	
}