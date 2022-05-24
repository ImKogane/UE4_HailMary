// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InteractionBase/InteractibleElement.h"
#include "ReversibleProps.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API AReversibleProps : public AInteractibleElement
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Elements details")
	bool IsReverse;
	
	UPROPERTY(VisibleAnywhere, Category = "Elements details")
	bool IsFalling;
	
	virtual void Interaction(AActor* Character) override;
	
};
