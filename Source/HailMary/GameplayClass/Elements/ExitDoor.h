// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleElement.h"
#include "ExitDoor.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API AExitDoor : public AInteractibleElement
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	

	UPROPERTY(EditAnywhere, Category="Door details")
	bool IsOpen;
	
	UPROPERTY(VisibleAnywhere, Category="Door details")
	bool IsOpening;
	
	UPROPERTY(VisibleAnywhere)
	AStudentCharacter* NearPlayer;

	
	
	class UMainGameInstance* TheGameInstance;
	
	
	UFUNCTION()
	void OpenDoor();
	
	virtual void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual void OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex) override;


public :

	virtual void Tick(float DeltaSeconds) override;

	
	
};
