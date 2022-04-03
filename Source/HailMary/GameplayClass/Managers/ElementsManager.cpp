// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementsManager.h"


// Sets default values
AElementsManager::AElementsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AElementsManager::BeginPlay()
{
	Super::BeginPlay();

	//SpawnBackDoor();
	
}

/*
/
// @brief Spawn back door on Elements Spawners
 
void AElementsManager::SpawnBackDoor()
{
	if(BD_Spawnpoints.Num() > BD_Count && BD_Count > 0)
	{
		int RandIndex = 0;
		FActorSpawnParameters Params;
		Params.Owner = this;
		
		for (int i = 1; i <= BD_Count; ++i)
		{
			RandIndex = FMath::RandRange(0, BD_Spawnpoints.Num()-1);

			FVector Loc = BD_Spawnpoints[RandIndex]->GetActorLocation();
			FRotator Rot = BD_Spawnpoints[RandIndex]->GetActorRotation();
			ABackDoor* Door = GetWorld()->SpawnActor<ABackDoor>(BPBackDoor, Loc, Rot, Params);
			
			BD_Spawnpoints.RemoveAt((RandIndex));

		}
	}
}

*/

// Called every frame
void AElementsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

