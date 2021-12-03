// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TaskItem_Object.h"
#include "TaskItem_Object.h"
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

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Task settings")
	TArray<FString> TaskList;

	UPROPERTY(VisibleInstanceOnly, Category="Task details")
	FString Task;
	

	UPROPERTY(EditAnywhere, Category="Task details")
	bool TaskUnlocked;

	UPROPERTY(EditAnywhere, Category="Task details")
	bool TaskCompleted;

	UPROPERTY(EditDefaultsOnly, Category="Items")
	TArray<TSubclassOf<ATaskItem_Object>> AvailableItems;

	UPROPERTY(VisibleAnywhere, Category="Items")
	AInteractibleItem* MainNeedItemName;
	
	UPROPERTY(VisibleAnywhere, Category="Items")
	AInteractibleItem* OtherNeedItemName;

	UPROPERTY(VisibleAnywhere)
	TArray<AStudentCharacter*> NearPlayers;
	

	
	
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


public :

	virtual void Tick(float DeltaSeconds) override;
	
	FORCEINLINE AInteractibleItem* GetMainNeedItemName() { return MainNeedItemName; }
	FORCEINLINE AInteractibleItem* GetOtherNeedItemName() { return OtherNeedItemName; }

	FORCEINLINE void SetMainItem(AInteractibleItem* Item) { MainNeedItemName = Item; }
	FORCEINLINE void SetOtherItem(AInteractibleItem* Item) { OtherNeedItemName = Item; }

	
	
};
