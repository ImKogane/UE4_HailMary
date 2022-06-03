// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleElement.h"
#include "Task_Object.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API ATask_Object : public AInteractibleElement
{
	GENERATED_BODY()

protected:
	#pragma region ProtectedVariables
		UPROPERTY(EditDefaultsOnly, Category="Task settings")
		TArray<FString> TaskStringList;
		UPROPERTY(VisibleInstanceOnly, Category="Task details")
		FString Task;
		UPROPERTY(VisibleAnywhere, Category="Task details")
		int TaskArea;
		UPROPERTY(EditAnywhere, Category="Task details")
		bool TaskUnlocked;
		UPROPERTY(EditAnywhere, Category="Task details")
		bool TaskCompleted;
		UPROPERTY(EditAnywhere, Category="Task details")
		bool TaskProgressionLocked;
		UPROPERTY(EditAnywhere, Category="Task HUD Text")
		FString _strDisplayTextLocked;
		UPROPERTY(EditAnywhere, Category="Task HUD Text")
		FString _strDisplayTextUnlocked;
		UPROPERTY(EditAnywhere, Category="Task HUD Text")
		FString _strDisplayTextCompleted;
		UPROPERTY(EditInstanceOnly, Category="Task details")
		class AStorageDoor* StorageDoor;
	
		UPROPERTY(EditAnywhere, Category="Items")
		AInteractibleItem* MainNeedItemName;
		UPROPERTY(EditAnywhere, Category="Items")
		AInteractibleItem* OtherNeedItemName;
		UPROPERTY(VisibleAnywhere)
		TArray<AStudentCharacter*> NearPlayers;
		UPROPERTY(EditAnywhere, Category="Parameters")
		int _nbPhase = -1;

		UPROPERTY(EditAnywhere, Category="Parameters")
		float DecreaseRate;
	#pragma endregion 

	#pragma region ProtectedFunctions
		virtual void BeginPlay() override;
		UFUNCTION()
		void GenerateTask();
		UFUNCTION()
		void UnlockTask();
		UFUNCTION()
		void CompleteTask();
		virtual void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
		
		virtual void OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex) override;

		virtual void Interaction(AActor* Character) override;
	#pragma endregion 

public :
	#pragma region PublicFunctions
		virtual void Tick(float DeltaSeconds) override;
	#pragma endregion 
	
	#pragma region Accessors
		FORCEINLINE AInteractibleItem* GetMainNeedItemName() { return MainNeedItemName; }
		FORCEINLINE AInteractibleItem* GetOtherNeedItemName() { return OtherNeedItemName; }
		FORCEINLINE void SetMainItem(AInteractibleItem* Item) { MainNeedItemName = Item; }
		FORCEINLINE void SetOtherItem(AInteractibleItem* Item) { OtherNeedItemName = Item; }
		FORCEINLINE void SetTaskArea(int area) { TaskArea = area; }
		FORCEINLINE int GetTaskArea() { return TaskArea; }
		FORCEINLINE bool IsTaskUnlocked() { return TaskUnlocked; }
		FORCEINLINE bool IsTaskCompleted() { return TaskCompleted; }
		FORCEINLINE int GetPhase(){return _nbPhase;}
	#pragma endregion 
};
