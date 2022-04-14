// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaDoor.h"

// Sets default values
AAreaDoor::AAreaDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Base"));
	BaseComponent->SetupAttachment(RootComponent);
	
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(BaseComponent);

}

// Called when the game starts or when spawned
void AAreaDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAreaDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAreaDoor::OpenDoor()
{
	Destroy(true);
}

