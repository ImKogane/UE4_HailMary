// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleItem.h"
#include "UsableItem_Object.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API AUsableItem_Object : public AInteractibleItem
{
	GENERATED_BODY()

public:
	AUsableItem_Object();

	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override ;

	UFUNCTION()
	virtual void Effect(AActor* actor);
};
