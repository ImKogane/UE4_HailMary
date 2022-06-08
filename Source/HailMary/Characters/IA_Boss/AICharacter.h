﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"
#include "AICharacter.generated.h"

UCLASS()
class HAILMARY_API AAICharacter : public ACharacter
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* BossAuraAudioComponent;
	
	/*The Behavior Tree of the Character */
	UPROPERTY(EditAnywhere, Category =AI)
	class UBehaviorTree* BehaviorTree;
	/*The Component which is used for the "seeing" sense of the AI*/
	UPROPERTY(VisibleAnywhere,Category="AI")
	class UPawnSensingComponent* PawnSensingComp;
	UPROPERTY(VisibleAnywhere,Category="AIDebug")
	AStudentCharacter* Character;
	UPROPERTY(VisibleAnywhere,Category="AIDebug")
	class AMyAIController* AIController;
	UPROPERTY(VisibleAnywhere, Category="Door")
	TArray<AActor*> m_arrDoors;
	UPROPERTY(VisibleAnywhere, Category="Door")
	AActor* NearestDoor;
	UPROPERTY(VisibleAnywhere, Category="MerryMaker")
	TArray<AActor*> m_arrMerryMaker;
	UPROPERTY(VisibleAnywhere, Category="MerryMaker")
	AActor* NearestMerryMaker;
	UPROPERTY()
	bool bAIVisible = false;
	UPROPERTY()
	float LastSeenTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Speed")
	float m_fTimeOut = 1.0f;

	
	
	// Sets default values for this character's properties
	AAICharacter();
	UFUNCTION()
	void Pick();
	UFUNCTION()
	void Drop();
	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);
	UFUNCTION()
	AActor* GetNearestDoor();
	UFUNCTION()
	AActor* GetNearestMerryMaker();
	UFUNCTION()
	float GetRunningSpeed() { return _fRunningSpeed; }
	UFUNCTION()
	void SetRunningSpeed(float speed) { _fRunningSpeed = speed; }
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION() void PlayBossAura();
	UFUNCTION() void StopBossAura();

	UFUNCTION() void SetDefaultSpeed();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
	AGameHUD * _gameHud;

	#pragma region ProtectedVariable
		UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Speed")
		float _fPlayerSeenSpeedMultiplicator = 1.2f;
		UPROPERTY(VisibleAnywhere, Category="Speed")
		float _fDefaultSpeed;
		UPROPERTY(VisibleAnywhere, Category="Speed")
		float _fRunningSpeed;
	#pragma endregion 
};
