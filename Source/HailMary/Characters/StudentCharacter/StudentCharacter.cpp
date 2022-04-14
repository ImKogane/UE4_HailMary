// Copyright Epic Games, Inc. All Rights Reserved.

#include "StudentCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "DrawDebugHelpers.h"
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
	GetCharacterMovement()->MaxWalkSpeedCrouched = _fCrouchSpeed;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AStudentCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Get References
	_gameHud = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	m_player1 = Cast<AStudentCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetCharacter());
	m_player2 = Cast<AStudentCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 1)->GetCharacter());
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AStudentCharacter::OnBeginOverlap);
	IsShooting = false;
	SetPlayerId();
	InstanciatePerks();
}

void AStudentCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CameraForAim();
	Sprint();
	DuringAim(1);
	DuringAim(2);
	ShootItem(1);
	ShootItem(2);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AStudentCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	SetInputsState(EnumInputsState::EnableAll);
}

FVector AStudentCharacter::GetPawnViewLocation() const
{
	if (FollowCamera)
	{
		return FollowCamera->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
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

void AStudentCharacter::ToggleSprint()
{
	if (IsPlayerSprint == false)
	{
		IsPlayerSprint = true;
	}
	else
	{
		IsPlayerSprint = false;
	}
}

void AStudentCharacter::Sprint()
{
	if (IsAiming == false && IsPlayerSprint)
	{
		GetCharacterMovement()->MaxWalkSpeed = _fSprintSpeed;
	}
	if (IsPlayerSprint == false)
	{
		GetCharacterMovement()->MaxWalkSpeed = _fWalkSpeed;
	}
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
	IsAiming = true;
}

void AStudentCharacter::UndoAim()
{
	IsAiming = false;
}

void AStudentCharacter::CameraForAim()
{
	if (IsAiming)
	{
		FVector LerpResult = {};
		AimStep += FApp::GetDeltaTime() * AimSpeed;
		LerpResult.X = FMath::Lerp(OffsetAim.X, 200.f, AimStep);
		LerpResult.Y = FMath::Lerp(OffsetAim.Y, 50.f, AimStep);
		LerpResult.Z = FMath::Lerp(OffsetAim.Z, 50.f, AimStep);
		GetCharacterMovement()->MaxWalkSpeed = _fWalkSpeed;
		GetCameraBoom()->SocketOffset = LerpResult;
		_gameHud->GetDefaultWidget()->ShowCrosshairPlayer(GetPlayerId());
	}
	else
	{
		FVector LerpResult = {};
		AimStep -= FApp::GetDeltaTime() * AimSpeed;
		LerpResult.X = FMath::Lerp(OffsetAim.X, 200.f, AimStep);
		LerpResult.Y = FMath::Lerp(OffsetAim.Y, 50.f, AimStep);
		LerpResult.Z = FMath::Lerp(OffsetAim.Z, 50.f, AimStep);
		GetCameraBoom()->SocketOffset = LerpResult;
		_gameHud->GetDefaultWidget()->HideCrosshairPlayer(GetPlayerId());
	}
	AimStep = FMath::Clamp(AimStep, 0.f, 1.f);
}

void AStudentCharacter::DuringAim(int nbPlayerId)
{
	if (nbPlayerId == 1 && m_player1)
	{
		if (m_player1->IsAiming)
		{
			APlayerCameraManager* Camera = UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerCameraManager;
			FRotator newRotation = { 0.0, Camera->GetCameraRotation().Yaw, Camera->GetCameraRotation().Roll };
			m_player1->SetActorRotation(newRotation);
			if (m_player1->ItemInInventory != nullptr && m_player1->ItemInInventory->GetIsTaskItem() == false)
			{
				if (m_player1->ItemInInventory->GetIsTake() == true)
				{
					m_player1->ItemInInventory->ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					m_player1->ItemInInventory->ItemMesh->AttachToComponent(m_player1->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ItemSocket"));
					m_player1->ItemInInventory->SetActorLocation(m_player1->GetMesh()->GetSocketLocation("ItemSocket"));
				}
			}
		}
		else
		{
			if (m_player1->ItemInInventory != nullptr && m_player1->ItemInInventory->GetIsTaskItem() == false)
			{
				if (m_player1->ItemInInventory->GetIsTake() == true)
				{
					m_player1->ItemInInventory->ItemMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
					FVector Zero = FVector(0, 0, 0);
					m_player1->ItemInInventory->SetActorLocation(Zero);
				}
			}
		}
	}

	if (nbPlayerId == 2 && m_player2)
	{
		if (m_player2->IsAiming)
		{
			APlayerCameraManager* Camera = UGameplayStatics::GetPlayerController(GetWorld(), 1)->PlayerCameraManager;
			FRotator newRotation = { 0.0, Camera->GetCameraRotation().Yaw, Camera->GetCameraRotation().Roll };
			m_player2->SetActorRotation(newRotation);
			if (m_player2->ItemInInventory != nullptr && m_player2->ItemInInventory->GetIsTaskItem() == false)
			{
				if (m_player2->ItemInInventory->GetIsTake() == true)
				{
					m_player2->ItemInInventory->ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					m_player2->ItemInInventory->ItemMesh->AttachToComponent(m_player2->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ItemSocket"));
					m_player2->ItemInInventory->SetActorLocation(m_player2->GetMesh()->GetSocketLocation("ItemSocket"));
				}
			}
		}
		else
		{
			if (m_player2->ItemInInventory != nullptr && m_player2->ItemInInventory->GetIsTaskItem() == false)
			{
				if (m_player2->ItemInInventory->GetIsTake() == true)
				{
					m_player2->ItemInInventory->ItemMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
					FVector Zero = FVector(0, 0, 0);
					m_player2->ItemInInventory->SetActorLocation(Zero);
				}
			}
		}
	}
}

void AStudentCharacter::Shoot()
{
	if (IsAiming)
	{
		IsShooting = true;
	}	
}

void AStudentCharacter::ShootItem(int nbPlayerId)
{
	if (nbPlayerId == 1 && m_player1)
	{
		if (m_player1->IsShooting == true)
		{
			if (m_player1->IsAiming && m_player1->ItemInInventory != nullptr)
			{
				if (m_player1->ItemInInventory->GetIsTaskItem() == false && m_player1->ItemInInventory->GetIsTake() == true)
				{
					FVector ShootDirection = m_player1->CameraBoom->GetForwardVector();

					m_player1->ItemInInventory->ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					m_player1->ItemInInventory->ItemMesh->SetSimulatePhysics(true);
					m_player1->ItemInInventory->ItemMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
					m_player1->ItemInInventory->ItemMesh->AddForce(ShootDirection * 100000 * m_player1->ItemInInventory->ItemMesh->GetMass());
					m_player1->ItemInInventory->SetIsTake(false);
					m_player1->ItemInInventory = nullptr;
					m_player1->IsShooting = false;
					_gameHud->GetDefaultWidget()->UpdateItems();
				}
			}
			else
			{
				m_player1->IsShooting = false;
			}
		}
	}
	if (nbPlayerId == 2 && m_player2)
	{
		if (m_player2->IsShooting == true)
		{
			if (m_player2->IsAiming && m_player2->ItemInInventory != nullptr)
			{
				if (m_player2->ItemInInventory->GetIsTaskItem() == false && m_player2->ItemInInventory->GetIsTake() == true)
				{
					FVector ShootDirection = m_player2->CameraBoom->GetForwardVector();

					m_player2->ItemInInventory->ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					m_player2->ItemInInventory->ItemMesh->SetSimulatePhysics(true);
					m_player2->ItemInInventory->ItemMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
					m_player2->ItemInInventory->ItemMesh->AddForce(ShootDirection * 100000 * m_player2->ItemInInventory->ItemMesh->GetMass());
					m_player2->ItemInInventory->SetIsTake(false);
					m_player2->ItemInInventory = nullptr;
					m_player2->IsShooting = false;
					_gameHud->GetDefaultWidget()->UpdateItems();
				}
			}
			else
			{
				m_player2->IsShooting = false;
			}
		}
	}
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
		ItemHolder->Character->IsAiming = false;
		SetInputsState(EnumInputsState::DisableMovement);
		GetMesh()->bPauseAnims = true;

		//Hide Hud Progress bar
		if(_gameHud)
		{
			_gameHud->GetDefaultWidget()->HideProgressBar(GetPlayerId());
		}
	}
}

void AStudentCharacter::DropPlayer()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CameraBoom->bDoCollisionTest = true;
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SetInputsState(EnumInputsState::EnableAll);
	GetMesh()->bPauseAnims = false;
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

				PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AStudentCharacter::ToggleSprint);

				PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AStudentCharacter::CrouchPlayer);
				PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AStudentCharacter::UnCrouchPlayer);
	
				PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AStudentCharacter::Interact);

				PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AStudentCharacter::DoAction);
				PlayerInputComponent->BindAction("Action", IE_Released, this, &AStudentCharacter::UndoAction);

				PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AStudentCharacter::Aim);
				PlayerInputComponent->BindAction("Aim", IE_Released, this, &AStudentCharacter::UndoAim);

				PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AStudentCharacter::Shoot);
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
		case EnumInputsState::DisableMovementAndCamera :
		{
			PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AStudentCharacter::Interact);
			PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AStudentCharacter::DoAction);
			PlayerInputComponent->BindAction("Action", IE_Released, this, &AStudentCharacter::UndoAction);
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

