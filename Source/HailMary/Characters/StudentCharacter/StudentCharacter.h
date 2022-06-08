// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "HailMary/Characters/Perks/Perk_BaseComponent.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleElement.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleItem.h"
#include "HailMary/Interface/HUD/GameHUD.h"
#include "HailMary/GameSettings/HailMaryGameMode.h"
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
		FORCEINLINE float GetMakeTaskSpeed() { return MakeTaskSpeed; }
		FORCEINLINE float GetOpenDoorSpeed() { return OpenDoorSpeed; }
	
		FORCEINLINE bool GetSaveTaskState() { return SaveTaskState; }
		FORCEINLINE void SetSaveTaskState(bool state) { SaveTaskState = state; }

	
		void SetNearItem(AInteractibleItem* Item);
		UFUNCTION()
		FORCEINLINE AInteractibleItem* GetNearInteractibleItem(){return NearItem;}
		void SetNearElement(AInteractibleElement* Element);
		UFUNCTION()
		FORCEINLINE AInteractibleElement* GetNearInteractibleElement(){return NearElement;}
		UFUNCTION()
		UPerk_BaseComponent* GetPlayerPerk();
		UFUNCTION()
		FORCEINLINE int GetPlayerId(){return m_nbPlayerId;}
		UFUNCTION()
		FORCEINLINE TEnumAsByte<EnumInputsState> GetEnumInputsState(){return _enumInputsState;}
		UFUNCTION()
		FORCEINLINE float GetRunningSpeed(){return SprintSpeed;}
	#pragma endregion

protected:
	#pragma  region RuntimeVariables
		UPROPERTY()
		AGameHUD* _gameHud;
		UPROPERTY(VisibleAnywhere, Category="Player")
		int m_nbPlayerId = 0;
		UPROPERTY(VisibleAnywhere, Category="Movement")
		bool IsPlayerSprint;
		UPROPERTY(VisibleAnywhere, Category = "Item")
		AInteractibleItem* ItemInInventory;
		UPROPERTY(VisibleAnywhere, Category = "Item")
		AInteractibleItem* NearItem;
		UPROPERTY(VisibleAnywhere, Category = "Item")
		bool NoItem = true;
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
		bool IsShooting = false;
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
		float SprintSpeed = 500;
		UPROPERTY(EditDefaultsOnly, Category="Player stats")
		float WalkSpeed = 300;
		UPROPERTY(EditDefaultsOnly, Category="Player stats")
		float CrouchSpeed = 100;

		//Tasks
		UPROPERTY(EditDefaultsOnly, Category="Player stats")
		float MakeTaskSpeed = 0.005;
		UPROPERTY(VisibleAnywhere, Category="Player stats")
		bool SaveTaskState;
	
		UPROPERTY(EditDefaultsOnly, Category="Player stats")
		float OpenDoorSpeed = 0.05;
	
	#pragma endregion

	#pragma region Perks
		UPROPERTY(EditDefaultsOnly, Category="Player Perks")
		TSubclassOf<UPerk_BaseComponent> PlayerPerk_BP;
	
		UPROPERTY(EditDefaultsOnly, Category="Player Perks")
		UPerk_BaseComponent* PlayerPerk;
	
	
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
		void ToggleSprint();
		UFUNCTION()
		void Sprint();
	
		/** Player crouch system */
		UFUNCTION() void CrouchPlayer();
		UFUNCTION() void UnCrouchPlayer();
	
		UFUNCTION() void Interact();
		UFUNCTION() void DoAction();
		UFUNCTION() void UndoAction();

		/** Player aim system */
		UFUNCTION() void Aim();
		UFUNCTION() void UndoAim();
		UFUNCTION() void CameraForAim(AStudentCharacter* player);
		UFUNCTION() void DuringAim(AStudentCharacter* player);

		/** Player shoot system */
		UFUNCTION() void Shoot();
		UFUNCTION() void ShootItem(AStudentCharacter* player);

		/** Menus */
		UFUNCTION() void PauseGame();
		UFUNCTION() void UnpauseGame();
	
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
	#pragma endregion 


private :
	#pragma region PrivateFunctions
		UFUNCTION()
		void ItemSystem();
		UFUNCTION()
		void TakeItem();
		UFUNCTION()
		void SwitchItem();
	#pragma endregion 
};

