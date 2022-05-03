// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleItem.h"
#include "KeyItem_Object.generated.h"

UCLASS()
class HAILMARY_API AKeyItem_Object : public AInteractibleItem
{
	GENERATED_BODY()

public:
	AKeyItem_Object();
	
private:
	UPROPERTY(EditInstanceOnly, Category = "Key Details")
	int KeyItemArea;

public:
	FORCEINLINE void SetKeyArea(int area){KeyItemArea = area;}
	FORCEINLINE int GetKeyArea(){return KeyItemArea;}
	
};
