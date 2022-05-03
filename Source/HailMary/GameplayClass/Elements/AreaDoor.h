// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleElement.h"
#include "AreaDoor.generated.h"

class UBoxComponent;
UCLASS()
class HAILMARY_API AAreaDoor : public AInteractibleElement
{
	GENERATED_BODY()

	
	
public:	
	// Sets default values for this actor's properties
	AAreaDoor();
	
	virtual void Interaction(AActor* Character) override;
	void OpenDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UMainGameInstance* TheGameInstance;
	
	UPROPERTY(EditInstanceOnly, Category="Door details")
	int Area;
	
	

};
