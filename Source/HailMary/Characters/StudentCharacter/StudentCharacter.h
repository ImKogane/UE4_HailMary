// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "HailMary/Characters/Perks/Perk_BaseComponent.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleElement.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleItem.h"
#include "HailMary/Interface/HUD/GameHUD.h"
#include "StudentCharacter.generated.h"

#pragma region ForwardDeclarations
//	class UPerk_BaseComponent;
#pragma endregion


UENUM()
enum EnumInputsState
{
	EnableAll					UMETA(DisplayName = "Enable"),
	DisableMovementAndCamera	UMETA(DisplayName = "DisableMovementAndCamera"),	//Only Inputs Interact
	DisableMovementAndInputs	UMETA(DisplayName = "DisableMovementAndInputs"),	//Camera still free but no Inputs
	DisableMovement				UMETA(DisplayName = "DisableMovement"),				//Camera still free & Inputs
	DisableAll					UMETA(DisplayName = "DisableMovement")				
};

UCLASS(config=Game)
class AStudentCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	#pragma region PublicVariables
		/** Camera boom positioning the camera behind the character */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
		/** Follow camera */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
	#pragma endregion
	
	#pragma region PublicFunctions
		AStudentCharacter();
	    
		virtual void BeginPlay() override;
		/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
		float BaseTurnRate; 
		/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
		float BaseLookUpRate;
		UFUNCTION()
		virtual void Tick(float DeltaTime) override;
		UFUNCTION()
		void ResetInventory();
	    UFUNCTION()
	    void GrabPlayer(AActor* Holder);
		UFUNCTION()
		void DropPlayer();
		UFUNCTION()
		void SetInputsState(EnumInputsState newState);
	#pragma endregion PublicFunctions

	#pragma region Accessor
		/** Returns CameraBoom subobject **/
		FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
		/** Returns FollowCamera subobject **/
		FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
		FORCEINLINE AInteractibleItem* GetItemInInventory() { return ItemInInventory; }
		FORCEINLINE bool GetIsDoAction() { return IsDoAction; }
		FORCEINLINE float GetMakeTaskSpeed() { return _fMakeTaskSpeed; }
		FORCEINLINE float GetOpenDoorSpeed() { return _fOpenDoorSpeed; }
		void SetNearItem(AInteractibleItem* Item);
		UFUNCTION()
		FORCEINLINE AInteractibleItem* GetNearInteractibleItem(){return NearItem;}
		void SetNearElement(AInteractibleElement* Element);
		UFUNCTION()
		FORCEINLINE AInteractibleElement* GetNearInteractibleElement(){return NearElement;}
		UFUNCTION()
		UPerk_BaseComponent* GetFirstPerk();
		UFUNCTION()	
		UPerk_BaseComponent* GetSecondPerk();
		UFUNCTION()
		FORCEINLINE int GetPlayerId(){return m_nbPlayerId;}
		UFUNCTION()
		FORCEINLINE TEnumAsByte<EnumInputsState> GetEnumInputsState(){return _enumInputsState;}
		UFUNCTION()
		FORCEINLINE float GetRunningSpeed(){return _fSprintSpeed;}
	#pragma endregion

protected:
	#pragma  region RuntimeVariables
		UPROPERTY()
		AGameHUD * _gameHud;
		UPROPERTY(VisibleAnywhere, Category="Player")
		int m_nbPlayerId = 0;
		UPROPERTY(EditDefaultsOnly, Category="Movement")
		bool IsPlayerSprint;
		UPROPERTY(EditAnywhere, Category="Player")
		AInteractibleItem* ItemInInventory;
		UPROPERTY()
		AStudentCharacter* m_player1 = nullptr;
		UPROPERTY()
		AStudentCharacter* m_player2 = nullptr;
		UPROPERTY(VisibleAnywhere, Category="Player details")
		bool IsDoAction;
		UPROPERTY(VisibleAnywhere, Category = "Aim")
		FVector OffsetAim;
		UPROPERTY(VisibleAnywhere, Category = "Aim")
		bool IsAiming;
		UPROPERTY(VisibleAnywhere, Category = "Aim")
		float AimStep;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Aim")
		float AimSpeed;
		UPROPERTY(VisibleAnywhere, Category = "Shoot")
		bool IsShooting;
		UPROPERTY()
		AInteractibleItem* NearItem;
		UPROPERTY()
		AInteractibleElement* NearElement;
	    UPROPERTY(EditAnywhere)
	    USphereComponent* Collider;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		TEnumAsByte<EnumInputsState> _enumInputsState = EnumInputsState::EnableAll;
	#pragma endregion 
	
	///////////////////// PLAYER STATS /////////////////////
	#pragma region Player stats
		UPROPERTY(EditDefaultsOnly, Category="Player stats")
		float _fSprintSpeed;
		UPROPERTY(EditDefaultsOnly, Category="Player stats")
		float _fWalkSpeed;
		UPROPERTY(EditDefaultsOnly, Category="Player stats")
		float _fCrouchSpeed = 100;
		UPROPERTY(EditDefaultsOnly, Category="Player stats")
		float _fMakeTaskSpeed;
		UPROPERTY(EditDefaultsOnly, Category="Player stats")
		float _fOpenDoorSpeed;
	#pragma endregion

	#pragma region Perks
		UPROPERTY(EditDefaultsOnly, Category="Player Perks")
		TArray<TSubclassOf<UPerk_BaseComponent>> ArrPassivePerkBp;
		UPROPERTY(EditDefaultsOnly, Category="Player Perks")
		TArray<TSubclassOf<UPerk_BaseComponent>> ArrActivePerksBp;
		UPROPERTY(VisibleAnywhere, Category="Player Perks")
		TArray<UPerk_BaseComponent*> _arrPerks;
	#pragma endregion
	
	#pragma region ProtectedFunctions
	    UFUNCTION()
		void SetPlayerId();
	    UFUNCTION()
		void InstanciatePerks();
		/** Called for forwards/backward input */
	    UFUNCTION()
		void MoveForward(float Value);
		/** Called for side to side input */
	    UFUNCTION()
		void MoveRight(float Value);
		/** Player sprint system */
		UFUNCTION()
		void Sprint();
		UFUNCTION()
		void Walk();
		/** Player crouch system */
		UFUNCTION()
		void CrouchPlayer();
		UFUNCTION()
		void UnCrouchPlayer();
		UFUNCTION()
		void Interact();
		UFUNCTION()
		void DoAction();
		UFUNCTION()
		void UndoAction();
		UFUNCTION()
		void Aim();
		UFUNCTION()
		void UndoAim();
		UFUNCTION()
		void CameraForAim();
		UFUNCTION()
		void DuringAim(int nbPlayerId);
		UFUNCTION()
		void Shoot();
		UFUNCTION()
		void ShootItem(int nbPlayerId);
	    UFUNCTION()
	    void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/** 
		* Called via input to turn at a given rate. 
		* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
		*/
		void TurnAtRate(float Rate);
		/**
		* Called via input to turn look up/down at a given rate. 
		* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
		*/
		void LookUpAtRate(float Rate);
		// APawn interface
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
		// End of APawn interface
		virtual FVector GetPawnViewLocation() const override;
	#pragma endregion 


private :
	#pragma region PrivateFunctions
		UFUNCTION()
		void TakeItem();
		UFUNCTION()
		void SwitchItem();
	#pragma endregion 
};

