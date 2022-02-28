// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "InteractionBase/InteractibleElement.h"
#include "HidingSpot.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API AHidingSpot : public AInteractibleElement
{
	GENERATED_BODY()

	public:
		#pragma region Accessors
			FORCEINLINE bool GetContainPlayer(){return _bContainPlayer;}
		#pragma endregion

		#pragma region PublicFunction
			AHidingSpot();
			virtual void Interaction(AStudentCharacter* studentCharacter) override;
		#pragma endregion 
	
	protected:
		#pragma region ProtectedVariable
			UPROPERTY()
			bool _bContainPlayer = false;
			UPROPERTY(EditAnywhere)
			USceneComponent* _sceneComponentTeleportPosition;
		#pragma endregion 
	
		#pragma region ProtectedFunctions
			virtual void BeginPlay() override;
			UFUNCTION()
			void EnterLocker(AStudentCharacter* studentCharacter);
			UFUNCTION()
			void ResetLocker();
			virtual void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
			virtual void OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex) override;
		#pragma endregion

	
	private:
};
