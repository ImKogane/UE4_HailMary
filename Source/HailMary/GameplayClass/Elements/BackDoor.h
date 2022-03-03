// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleElement.h"
#include "BackDoor.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API ABackDoor : public AInteractibleElement
{
	GENERATED_BODY()

protected:
	

	UPROPERTY(VisibleAnywhere)
	class AStudentCharacter* NearPlayer;
	
	UPROPERTY(VisibleAnywhere)
	class AStudentCharacter* PlayerInside;
	
	
	UFUNCTION()
	void OpenDoor();
	
	virtual void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual void OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex) override;

public :
		virtual void Tick(float DeltaSeconds) override;

		bool GetPlayerIsInside();
	
	
};
