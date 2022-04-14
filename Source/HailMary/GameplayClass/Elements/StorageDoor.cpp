// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageDoor.h"

// Sets default values
AStorageDoor::AStorageDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Base"));
	BaseComponent->SetupAttachment(RootComponent);
	
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(BaseComponent);
	

}

// Called when the game starts or when spawned
void AStorageDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStorageDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStorageDoor::OpenDoor()
{
	Destroy(true);
}

