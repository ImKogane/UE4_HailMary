// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "Phase.generated.h"

UCLASS()
class HAILMARY_API APhase : public AActor
{
	GENERATED_BODY()
	
public:
	#pragma region PublicFunctions
		// Sets default values for this actor's properties
		APhase();
		// Called every frame
		virtual void Tick(float DeltaTime) override;
	#pragma endregion 
	
protected:
	#pragma region ProtectedVariables
		UPROPERTY(EditAnywhere, Category="Parameters")
		int _nbPhase = -1;
		UPROPERTY(VisibleAnywhere, Category="Parameters")
		TArray<ATargetPoint*> _arrTargetPoints;
	#pragma endregion

	#pragma region ProtectedFunctions
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
		UFUNCTION()
		virtual void Init();
	#pragma endregion 
};
