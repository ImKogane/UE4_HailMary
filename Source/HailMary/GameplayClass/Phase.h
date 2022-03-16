// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "HailMary/Characters/IA_Boss/BotTargetPoint.h"
#include "Phase.generated.h"

UCLASS()
class HAILMARY_API APhase : public AActor
{
	GENERATED_BODY()
	
public:
	#pragma region Accessors
		UFUNCTION()
		FORCEINLINE int GetPhase(){return _nbPhase;}
		FORCEINLINE TArray<ABotTargetPoint*> GetBotTargetPoints(){return _arrBotTargetPoints;}
	#pragma endregion 
	
	#pragma region PublicFunctions
		APhase();
		virtual void Tick(float DeltaTime) override;
	#pragma endregion 
	
protected:
	#pragma region ProtectedVariables
		UPROPERTY(EditAnywhere, Category="Parameters")
		int _nbPhase = -1;
		UPROPERTY(VisibleAnywhere, Category="Parameters")
		TArray<ABotTargetPoint*> _arrBotTargetPoints;
	#pragma endregion

	#pragma region ProtectedFunctions
		virtual void BeginPlay() override;
		UFUNCTION()
		virtual void Init();
	#pragma endregion 
};
