// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleElement.h"
#include "E_SpeakerMM.generated.h"

/**
 * 
 */
UCLASS()


class HAILMARY_API AE_SpeakerMM : public AInteractibleElement
{
	GENERATED_BODY()
	
public:
	#pragma region PublicFunctions
		AE_SpeakerMM();
		virtual void Interaction(AActor* Character) override;
		virtual void BeginPlay() override;
		UFUNCTION() void PlaySpeakerSound();
		UFUNCTION() void StopSpeakerSound();
	#pragma endregion

	#pragma region PublicVariables
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		UAudioComponent* SpeakerAudioComponent;
		UPROPERTY(EditAnywhere, Category = "Manager")
		class AMerryMaker_BossManager* MerryMakerManager;
	#pragma endregion

	#pragma region Accessor
		UFUNCTION()
		FORCEINLINE FVector GetEntrancePosition(){return _sceneComponentEntrancePosition->GetComponentLocation();}
		UFUNCTION()
		FORCEINLINE bool GetIsActivate(){return _bIsActivate; }
		// UFUNCTION()
		// FORCEINLINE void SetIsActivate(bool bValue){ _bIsActivate = bValue; }
	#pragma endregion 




protected:

	UPROPERTY(VisibleAnywhere, Category="Element details")
	bool _bIsActivate;
	UPROPERTY(EditAnywhere)
	USceneComponent* _sceneComponentEntrancePosition;
};
