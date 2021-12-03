// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleElement.h"
#include "HailMary/GameplayClass/InteractionBase/InteractibleItem.h"
#include "StudentCharacter.generated.h"

UCLASS(config=Game)
class AStudentCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
    
public:
	AStudentCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	bool IsPlayerSprint;

	UPROPERTY(EditAnywhere, Category="Player")
	AInteractibleItem* ItemInInventory;

	UPROPERTY(VisibleAnywhere, Category="Player details")
	bool IsDoAction;

	
	///////////////////// PLAYER STATS /////////////////////
#pragma region Player stats

	UPROPERTY(EditDefaultsOnly, Category="Player stats")
	float SprintSpeed;
	
	UPROPERTY(EditDefaultsOnly, Category="Player stats")
	float WalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category="Player stats")
	float CrouchSpeed = 100;
	
	UPROPERTY(EditDefaultsOnly, Category="Player stats")
	float MakeTaskSpeed;
	
	UPROPERTY(EditDefaultsOnly, Category="Player stats")
	float OpenDoorSpeed;

	
#pragma endregion 

	
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
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

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

private :

	UPROPERTY()
	AInteractibleItem* NearItem;

	UPROPERTY()
	AInteractibleElement* NearElement;

	UFUNCTION()
	void TakeItem();

	UFUNCTION()
	void SwitchItem();

	


public:
	
	UFUNCTION()
	void ResetInventory();
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	FORCEINLINE AInteractibleItem* GetItemInInventory() { return ItemInInventory; }
	FORCEINLINE bool GetIsDoAction() { return IsDoAction; }
	FORCEINLINE float GetMakeTaskSpeed() { return MakeTaskSpeed; }
	FORCEINLINE float GetOpenDoorSpeed() { return OpenDoorSpeed; }
	
	FORCEINLINE void SetNearItem(AInteractibleItem* Item) { NearItem = Item; }
	FORCEINLINE void SetNearElement(AInteractibleElement* Element) { NearElement = Element; }
};

