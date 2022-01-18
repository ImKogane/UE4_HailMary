// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HailMary/GameplayClass/BackDoor.h"
#include "ElementsManager.generated.h"

UCLASS()
class HAILMARY_API AElementsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElementsManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnBackDoor();

	UPROPERTY(EditDefaultsOnly, Category = "Back Door system")
	TSubclassOf<ABackDoor> BPBackDoor;

	UPROPERTY(EditInstanceOnly, Category = "Back Door system")
	TArray<AActor*> BD_Spawnpoints;
	
	UPROPERTY(EditInstanceOnly, Category = "Back Door system")
	int BD_Count;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
