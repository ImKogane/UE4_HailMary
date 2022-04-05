// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleElement.h"
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
			UFUNCTION()
			void SetPlayerInside(AStudentCharacter* player);
			virtual void Interaction(AStudentCharacter* studentCharacter) override;
		#pragma endregion

		#pragma region Accessors
			UFUNCTION()
			bool GetPlayerIsInside();
			UFUNCTION()
			FORCEINLINE FVector GetEntrancePosition(){return _sceneComponentEntrancePosition->GetComponentLocation();}
			UFUNCTION()
			FORCEINLINE FVector GetTeleportPosition(){return _sceneComponentTeleportPosition->GetComponentLocation();}
			UFUNCTION()
			FORCEINLINE UCameraComponent* GetCameraComponent(){return _cameraComponent;}
		#pragma endregion 
	
	protected:
		#pragma region ProtectedVariables
			UPROPERTY(VisibleAnywhere)
			class AStudentCharacter* NearPlayer;
			UPROPERTY(VisibleAnywhere)
			class AStudentCharacter* PlayerInside;
			UPROPERTY(EditAnywhere)
			USceneComponent* _sceneComponentEntrancePosition;
			UPROPERTY(EditAnywhere)
			USceneComponent* _sceneComponentTeleportPosition;
			UPROPERTY(EditAnywhere)
			UCameraComponent* _cameraComponent;
			UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
			UAudioComponent* _audioComponent;
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
