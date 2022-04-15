// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlueArea.h"
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
	AGluePot();
	virtual void BeginPlay() override;
	virtual void Effect(AActor*	actor) override;

protected:
	UPROPERTY(EditAnywhere, Category="gluepot")
	TSubclassOf<AGlueArea> _bpGlueArea;

};
