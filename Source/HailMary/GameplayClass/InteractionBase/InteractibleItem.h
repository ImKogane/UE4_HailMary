// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "InteractibleItem.generated.h"

UCLASS()
class HAILMARY_API AInteractibleItem : public AActor
{
	GENERATED_BODY()
	
	public:
		#pragma region PublicFunctions
			// Sets default values for this actor's properties
    		AInteractibleItem();
			// Called every frame
			virtual void Tick(float DeltaTime) override;
			UFUNCTION()
			void Take();
			UFUNCTION()
			void Drop(FVector NewLocation);
			UFUNCTION()
			void Use();
		#pragma endregion

		#pragma region Accessors
			FORCEINLINE FString GetItemName() { return ItemName; }
			FORCEINLINE bool GetIsTaskItem() { return IsTaskItem; }
			FORCEINLINE bool GetIsTake() { return IsTake; }
			FORCEINLINE UTexture2D* GetItemArtwork() { return ItemArtwork; }
			FORCEINLINE void SetIsTake(bool bIsTake) { IsTake = bIsTake; }
		#pragma endregion 
		
		#pragma region PublicVariables
			UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
			USceneComponent* BaseComponent;
			UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
			UStaticMeshComponent* ItemMesh;
			UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
			UBoxComponent* CollisionBox;
		#pragma endregion 

protected:
	#pragma region ProtectedFunctions
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
		UFUNCTION()
		virtual void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
				int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		UFUNCTION()
		void OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex);
	#pragma endregion 

	#pragma region ProtectedVariables
		UPROPERTY(EditDefaultsOnly, Category="Item details")
		FString ItemName;
		UPROPERTY(EditDefaultsOnly, Category="Item details")
		UTexture2D* ItemArtwork;
		UPROPERTY(VisibleAnywhere, Category="Item details")
		bool IsTake;
		UPROPERTY(VisibleAnywhere, Category="Item details")
		bool IsTaskItem;
	#pragma endregion 
};
