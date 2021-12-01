// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StudentCharacter.h"
#include "Business_StudentCharacter.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API ABusiness_StudentCharacter : public AStudentCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Class details")
	float TaskSpeedBoost;
	
protected:
	virtual void BeginPlay() override;
	
};
