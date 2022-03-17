// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MerryMaker_BossManager.generated.h"

UCLASS()
class HAILMARY_API AMerryMaker_BossManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMerryMaker_BossManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category = "Merry Maker Elements")
	TArray<class AE_SpeakerMM*> ActivesSpeakers;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void AddActiveSpeaker(AE_SpeakerMM* speaker);

};
