// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleItem.h"
#include "KeyItem_Object.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API AKeyItem_Object : public AInteractibleItem
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly, Category = "Key Details")
	int KeyArea;

public:
	FORCEINLINE int GetKeyArea(){return KeyArea;}
	
};
