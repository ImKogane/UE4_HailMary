// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InteractionBase/InteractibleElement.h"
#include "Components/TimelineComponent.h"
#include "ReversibleProps.generated.h"

/**
 * 
 */

class UCurveFloat;

UCLASS()
class HAILMARY_API AReversibleProps : public AInteractibleElement
{
	GENERATED_BODY()

	AReversibleProps();
	
protected:

	
	
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category = "Elements details")
	bool IsReverse;
	
	UPROPERTY(VisibleAnywhere, Category = "Elements details")
	bool IsFalling;

	//Timeline
	virtual void Interaction(AActor* Character) override;

	UFUNCTION()
	void FallEffect();

	FTimeline CurveTimeLine;

	UPROPERTY(EditAnywhere, Category="Timeline")
	UCurveFloat* CurveFloat;
	
	FTimerHandle TimerHandle;

	float DELTATIME;

	UPROPERTY()
	FRotator StartRot;

	UPROPERTY()
	FRotator EndRot;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	float ZOffset;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION()
	void TimeLineProgress(float Value);

	FORCEINLINE bool GetIsFalling(){ return IsFalling;}
	FORCEINLINE bool GetIsReverse(){ return IsReverse;}
	
};
