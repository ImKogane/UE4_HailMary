// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "BotTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API ABotTargetPoint : public ATargetPoint
{
	GENERATED_BODY()

	public:
		#pragma region Accessors
			FORCEINLINE int GetPhase(){return _nbPhase;}
		#pragma endregion 
		
	protected:
		#pragma region ProtectedVariables
			UPROPERTY(EditAnywhere, Category="Parameters")
			int _nbPhase = -1;
		#pragma endregion

		#pragma region ProtectedFunction
			UFUNCTION()
			virtual void BeginPlay() override;
		#pragma endregion 
};
