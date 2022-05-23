// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "InteractibleElement.generated.h"

#pragma region ForwardDeclaration
	class AStudentCharacter;
	class AGameHUD;
	class UMainGameInstance;
#pragma endregion

UCLASS()
class HAILMARY_API AInteractibleElement : public AActor
{
	GENERATED_BODY()
	
public:
	#pragma region PublicVariables
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
		USceneComponent* BaseComponent;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ElementMesh;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* CollisionBox;
	#pragma endregion
	
	#pragma region PublicFunctions
		// Sets default values for this actor's properties
		AInteractibleElement();
		// Called every frame
		virtual void Tick(float DeltaTime) override;
		UFUNCTION()
		virtual void Interaction(AActor* Character);
	#pragma endregion 
	
	#pragma region Accessors
		FORCEINLINE FString GetDisplayText(){return _strDisplayText;}
		FORCEINLINE void SetHudEnable(bool value) { _bIsHudEnable = value; }
		FORCEINLINE bool GetIsHudEnable(){return _bIsHudEnable;}
	#pragma endregion 
	
protected:
	#pragma region ProtectedVariables
		UPROPERTY()
		UMainGameInstance* _gameInstance;
		UPROPERTY()
		AGameHUD * _gameHud;
		UPROPERTY(EditDefaultsOnly, Category="Element details")
		FString ElementName;
		UPROPERTY(EditDefaultsOnly, Category="Element details")
		FString _strDisplayText;
		UPROPERTY(EditDefaultsOnly, Category="Element details")
		float ElementMaxProgress;
		UPROPERTY(VisibleAnywhere, Category="Element stats")
		float ElementProgress;
		UPROPERTY(VisibleAnywhere, Category="Element stats")
		int ElementInteractionCount;
		UPROPERTY(EditAnywhere, Category="Element stats")
		bool _bIsHudEnable = true;
	#pragma endregion
	
	#pragma region ProtectedFunctions
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
		UFUNCTION()
		virtual void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		UFUNCTION()
		virtual void OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex);
	#pragma endregion 


};
