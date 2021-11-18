// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TaskSpawner.generated.h"

UCLASS()
class HAILMARY_API ATaskSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATaskSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, Category="Task details")
	int TaskArea;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
