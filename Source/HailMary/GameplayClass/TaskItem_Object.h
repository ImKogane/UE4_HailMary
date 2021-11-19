// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleItem.h"
#include "TaskItem_Object.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API ATaskItem_Object : public AInteractibleItem
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USceneComponent* BaseComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ItemMesh;

	protected:

	UPROPERTY(EditDefaultsOnly, Category="Item details")
	FString ItemName;

	public:
	ATaskItem_Object();

	
};
