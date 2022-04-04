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
	AE_SpeakerMM();
	
	virtual void Interaction(AStudentCharacter* studentCharacter) override;
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* SpeakerAudioComponent;

	UPROPERTY(EditAnywhere, Category = "Manager")
	class AMerryMaker_BossManager* MerryMakerManager;

	UFUNCTION() void PlaySpeakerSound();
	UFUNCTION() void StopSpeakerSound();

protected:

	UPROPERTY(VisibleAnywhere, Category="Element details")
	bool IsActivate;
	
};
