// Copyright Epic Games, Inc. All Rights Reserved.

#include "StudentCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/SpringArmComponent.h"
#include "HailMary/Characters/IA_Boss/AICharacter.h"
#include "HailMary/GameplayClass/Elements/Task_Object.h"
#include "HailMary/Interface/HUD/GameHUD.h"
#include "Kismet/GameplayStatics.h"

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
	
	Collider = CreateDefaultSubobject<USphereComponent>(FName("Collider"));
	Collider->SetupAttachment(GetMesh());
	
	GetCharacterMovement()->MaxWalkSpeed = 200;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AStudentCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Get References
	_gameHud = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AStudentCharacter::OnBeginOverlap);
	SetPlayerId();
	InstanciatePerks();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AStudentCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	SetInputsState(EnumInputsState::EnableAll);
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

void AStudentCharacter::SetPlayerId()
{
	if(UGameplayStatics::GetPlayerControllerID(Cast<APlayerController>(Controller)) == 0 )
	{
		m_nbPlayerId = 1;
	}
	else
	{
		m_nbPlayerId = 2;
	}
}

void AStudentCharacter::InstanciatePerks()
{
	UWorld* world = GetWorld();
	
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
	//NearItem = tempItem;
	SetNearItem(tempItem);
	NearItem->SetIsTake(false);
}

void AStudentCharacter::ResetInventory()
{
	AInteractibleItem* TempItem;
	TempItem = ItemInInventory;
	ItemInInventory = nullptr;
	TempItem->Destroy(true);
}

void AStudentCharacter::SetNearItem(AInteractibleItem* Item)
{
	NearItem = Item;
	if(_gameHud)
	{
		_gameHud->GetDefaultWidget()->UpdateDisplayText();
	}
}

void AStudentCharacter::SetNearElement(AInteractibleElement* Element)
{
	NearElement = Element;
	if(_gameHud)
	{
		_gameHud->GetDefaultWidget()->UpdateDisplayText();
	}
}

UPerk_BaseComponent* AStudentCharacter::GetFirstPerk()
{
	if( _arrPerks.Num() > 0)
	{
		 return  _arrPerks[0];
	}
	return nullptr;
}

UPerk_BaseComponent* AStudentCharacter::GetSecondPerk()
{
	if( _arrPerks.Num() > 1)
	{
		return  _arrPerks[1];
	}
	return  nullptr;
}

void AStudentCharacter::TakeItem()
{
	ItemInInventory = NearItem;
	NearItem->Take();
	NearItem = nullptr;
	if(_gameHud)
	{
		_gameHud->GetDefaultWidget()->UpdateItems();
	}
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
		NearElement->Interaction(this);
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

void AStudentCharacter::Aim()
{
	OffsetAim = { 200.0, 50.0, 50.0 };
	GetCameraBoom()->SocketOffset = OffsetAim;
	_gameHud->GetDefaultWidget()->ShowCrosshairPlayer(GetPlayerId());
}

void AStudentCharacter::UndoAim()
{
	OffsetAim = { 0.0, 0.0, 0.0 };
	GetCameraBoom()->SocketOffset = OffsetAim;
	_gameHud->GetDefaultWidget()->HideCrosshairPlayer(GetPlayerId());
}

void AStudentCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(AAICharacter::StaticClass()))
	{
		if( Cast<AAICharacter>(OtherActor)->Character == nullptr)
		{
			Cast<AAICharacter>(OtherActor)->Character = this;
		}
	}
}

void AStudentCharacter::GrabPlayer(AActor* Holder)
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CameraBoom->bDoCollisionTest = false;
	if(Holder->IsA(AAICharacter::StaticClass()))
	{
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Collision"));
		AAICharacter* ItemHolder = Cast<AAICharacter>(Holder);
		AttachToComponent(ItemHolder->GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Socket_test"));
		ItemHolder->Character = this;
		SetInputsState(EnumInputsState::DisableMovement);

		//Hide Hud Progress bar
		if(_gameHud)
		{
			_gameHud->GetDefaultWidget()->HideProgressBar(this->GetPlayerId());
		}
	}
}

void AStudentCharacter::DropPlayer()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CameraBoom->bDoCollisionTest = true;
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SetInputsState(EnumInputsState::EnableAll);
}

void AStudentCharacter::SetInputsState(EnumInputsState newState)
{
	//Assign New input state
	_enumInputsState = newState;
	
	//Remove all inputs
	UInputComponent* PlayerInputComponent = InputComponent;
	PlayerInputComponent->ClearActionBindings();
	PlayerInputComponent->AxisBindings.Empty();
	UndoAction();

	//Setup new inputs according to the new state
	switch (_enumInputsState)
	{
		case EnumInputsState::EnableAll :
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

				PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AStudentCharacter::Aim);
				PlayerInputComponent->BindAction("Aim", IE_Released, this, &AStudentCharacter::UndoAim);
		}
		case EnumInputsState::DisableMovement :
		{
				PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
				PlayerInputComponent->BindAxis("TurnRate", this, &AStudentCharacter::TurnAtRate);
				PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
				PlayerInputComponent->BindAxis("LookUpRate", this, &AStudentCharacter::LookUpAtRate);
					
				// PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AStudentCharacter::Interact);
				// PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AStudentCharacter::DoAction);
				// PlayerInputComponent->BindAction("Action", IE_Released, this, &AStudentCharacter::UndoAction);
		}
		case EnumInputsState::DisableMovementAndInputs :
		{
			//none
		}
		case EnumInputsState::DisableAll :
		{
			//none
		}
	}
}

