// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HailMary/GameplayClass/UsableItem_Object.h"
#include "GluePot.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API AGluePot : public AUsableItem_Object
{
	GENERATED_BODY()
	
public: 

	virtual void Effect() override;
};
