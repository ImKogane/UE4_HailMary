// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionBase/InteractibleElement.h"
#include "BackDoor.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API ABackDoor : public AInteractibleElement
{
	GENERATED_BODY()

	public :
		#pragma region PublicFunctions
			ABackDoor();
			virtual void Tick(float DeltaSeconds) override;
		#pragma endregion 
	
	protected:
		#pragma region ProtectedVariables
			UPROPERTY(VisibleAnywhere)
			class AStudentCharacter* NearPlayer;
			UPROPERTY(EditAnywhere)
			USceneComponent* _sceneComponentEntrancePosition;
			UPROPERTY(EditAnywhere)
			USceneComponent* _sceneComponentTeleportPosition;
		#pragma endregion

		#pragma region ProtectedFunctions
			UFUNCTION()
			void OpenDoor();
			virtual void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
			virtual void OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex) override;
		#pragma endregion 
};
