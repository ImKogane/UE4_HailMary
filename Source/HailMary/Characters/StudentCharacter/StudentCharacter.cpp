// Copyright Epic Games, Inc. All Rights Reserved.

#include "StudentCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "HailMary/GameplayClass/Task_Object.h"

//////////////////////////////////////////////////////////////////////////
// AHailMaryCharacter

AStudentCharacter::AStudentCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	

	GetCharacterMovement()->MaxWalkSpeed = 200;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AStudentCharacter::BeginPlay()
{
	Super::BeginPlay();
	InstanciatePerks();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AStudentCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveForward", this, &AStudentCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AStudentCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AStudentCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AStudentCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AStudentCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AStudentCharacter::Walk);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AStudentCharacter::CrouchPlayer);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AStudentCharacter::UnCrouchPlayer);
	
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AStudentCharacter::Interact);
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AStudentCharacter::DoAction);
	PlayerInputComponent->BindAction("Action", IE_Released, this, &AStudentCharacter::UndoAction);

	
}

/////////////////////// PLAYER MOVEMENT ///////////////////////
#pragma region Player movement

void AStudentCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AStudentCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AStudentCharacter::InstanciatePerks()
{
	for (TSubclassOf<UPerk_BaseComponent> currentPassivePerk : ArrPassivePerkBp)
	{
		_arrPerks.Add(NewObject<UPerk_BaseComponent>(this, currentPassivePerk));
	}

	for (TSubclassOf<UPerk_BaseComponent> currentActivePerk : ArrActivePerksBp)
	{
		_arrPerks.Add(NewObject<UPerk_BaseComponent>(this ,currentActivePerk));
	}
}

void AStudentCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AStudentCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AStudentCharacter::Sprint()
{
	IsPlayerSprint = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AStudentCharacter::Walk()
{
	IsPlayerSprint = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AStudentCharacter::CrouchPlayer()
{
	Crouch(true);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Crouch"));
}

void AStudentCharacter::UnCrouchPlayer()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Uncrouch"));
	UnCrouch(true);
}

#pragma endregion

/////////////////////// PLAYER INVENTORY ///////////////////////
#pragma region Player inventory

void AStudentCharacter::SwitchItem()
{
	FVector tempLocation = NearItem->GetActorLocation();
	AInteractibleItem* tempItem = ItemInInventory;

	TakeItem();

	tempItem->Drop(tempLocation);
	NearItem = tempItem;
	NearItem->SetIsTake(false);
}

void AStudentCharacter::ResetInventory()
{
	AInteractibleItem* TempItem;
	TempItem = ItemInInventory;
	ItemInInventory = nullptr;
	TempItem->Destroy(true);
}

UPerk_BaseComponent* AStudentCharacter::GetFirstPerk()
{
	if( _arrPerks.Num() > 0)
	{
		 return  _arrPerks[0];
	}
	// if( ArrPassivePerk.Num() > 0 )
	// {
	// 	return Cast<UPerk_BaseComponent>(ArrPassivePerk[0]);
	// }
	// if ( ArrActivePerks.Num() > 0 )
	// {
	// 	return Cast<UPerk_BaseComponent>(ArrActivePerks[0]);
	// }
	return nullptr;
}

UPerk_BaseComponent* AStudentCharacter::GetSecondPerk()
{
	if( _arrPerks.Num() > 1)
	{
		return  _arrPerks[1];
	}
	
	// UPerk_BaseComponent* SecondPerk = nullptr;
	//
	// if( ArrPassivePerk.Num() > 1 )
	// {
	// 	SecondPerk =  Cast<UPerk_BaseComponent>(ArrPassivePerk[1]);
	// 	return SecondPerk;
	// }
	//
	// if ( ArrActivePerks.Num() > 0 )
	// {
	// 	SecondPerk = Cast<UPerk_BaseComponent>(ArrActivePerks[0]);
	// 	if( SecondPerk == GetFirstPerk() )
	// 	{
	// 		SecondPerk = nullptr ;
	// 	}
	// 	else
	// 	{
	// 		if( ArrActivePerks.Num() > 1 )
	// 		{
	// 			SecondPerk = Cast<UPerk_BaseComponent>(ArrActivePerks[1]);
	// 		}
	// 	}
	// }
	//
	// return SecondPerk;

	return  nullptr;
}

void AStudentCharacter::TakeItem()
{
	ItemInInventory = NearItem;
	NearItem->Take();
	NearItem = nullptr;
}

#pragma endregion 

void AStudentCharacter::Interact()
{
	if(NearItem != nullptr)
	{
		if(ItemInInventory == nullptr)
		{
			//First item take
			TakeItem();	
			
		}
		//If player already have item in his inventory
		else
		{
			SwitchItem();
		}
		
	}

	if(NearElement != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("Element interaction"));
	}
}

/**
 * @brief 
 */
void AStudentCharacter::DoAction()
{
	IsDoAction = true;
}

void AStudentCharacter::UndoAction()
{
	IsDoAction = false;
}



