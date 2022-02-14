// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayCycle.generated.h"

UCLASS()
class HAILMARY_API APlayCycle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayCycle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	int InitialLoopTime;
	
	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
	int LoopTime;

	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
	FTimerHandle GameTimer;

	UFUNCTION()
	void Loop();

	UFUNCTION()
	void Clock();

	UFUNCTION()
	void ShowTimer();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ResetTimer();
	
	UFUNCTION()
	void StopTimer();

};
