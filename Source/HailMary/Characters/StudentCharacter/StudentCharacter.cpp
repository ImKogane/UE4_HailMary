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
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AStudentCharacter::OnBeginOverlap);
	SetPlayerId();
	InstanciatePerks();
}

void AStudentCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Sprint();
	AHailMaryGameMode* _gameMode = Cast<AHailMaryGameMode>(GetWorld()->GetAuthGameMode());
	for (AStudentCharacter* player : _gameMode->Players)
	{
		CameraForAim(player);
		DuringAim(player);
		ShootItem(player);
	}
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
	//
}

void AStudentCharacter::UnCrouchPlayer()
{
	//
}

#pragma endregion

/////////////////////// PLAYER INVENTORY ///////////////////////
#pragma region Player inventory

void AStudentCharacter::SwitchItem()
{
	FVector tempLocation = NearItem->GetActorLocation();
	AInteractibleItem* tempItem = ItemInInventory;
	tempItem->Drop(tempLocation);
	TakeItem();
	SetNearItem(tempItem);
	NearItem->SetIsTake(false);
}

void AStudentCharacter::ResetInventory()
{
	AInteractibleItem* TempItem;
	TempItem = ItemInInventory;
	ItemInInventory = nullptr;
	TempItem->Destroy(true);
	NoItem = true;
	
	if( _gameHud)
	{
		_gameHud->GetDefaultWidget()->UpdateItems();
	}
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

void AStudentCharacter::ItemSystem()
{
	if (NoItem)
	{
		if (NearItem != nullptr && ItemInInventory == nullptr && IsAiming == false)
		{
			TakeItem();
		}
	}
	else
	{
		if (NearItem != nullptr && ItemInInventory != nullptr && IsAiming == false)
		{
			SwitchItem();
		}
	}
}

void AStudentCharacter::TakeItem()
{
	ItemInInventory = NearItem;
	NearItem->Take();
	NearItem = nullptr;
	NoItem = false;
	if(_gameHud)
	{
		_gameHud->GetDefaultWidget()->UpdateItems();
	}
}

#pragma endregion 

void AStudentCharacter::Interact()
{
	if(NearElement != nullptr)
	{
		NearElement->Interaction(this);
	}
}

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

void AStudentCharacter::CameraForAim(AStudentCharacter* player)
{
	if (IsAiming)
	{
		if (player->ItemInInventory != nullptr && player->ItemInInventory->GetIsTaskItem() == false)
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

void AStudentCharacter::DuringAim(AStudentCharacter* player)
{
	if (player != nullptr)
	{
		if (player->IsAiming)
		{
			if (player->ItemInInventory != nullptr && player->ItemInInventory->GetIsTaskItem() == false)
			{
				APlayerCameraManager* Camera = Cast<APlayerController>(player->GetController())->PlayerCameraManager;
				FRotator newRotation = { 0.0, Camera->GetCameraRotation().Yaw, Camera->GetCameraRotation().Roll };
				player->SetActorRotation(newRotation);
				if (player->ItemInInventory != nullptr && player->ItemInInventory->GetIsTaskItem() == false)
				{
					if (player->ItemInInventory->GetIsTake() == true)
					{
						player->ItemInInventory->ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
						player->ItemInInventory->AttachToComponent(player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ItemSocket"));
						player->ItemInInventory->SetActorLocation(player->GetMesh()->GetSocketLocation("ItemSocket"));
					}
				}
			}
		}
		else
		{
			if (player->ItemInInventory != nullptr && player->ItemInInventory->GetIsTaskItem() == false)
			{
				if (player->ItemInInventory->GetIsTake() == true)
				{
					player->ItemInInventory->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
					FVector Zero = FVector(0, 0, 0);
					player->ItemInInventory->SetActorLocation(Zero);
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

void AStudentCharacter::ShootItem(AStudentCharacter* player)
{
	if (player != nullptr)
	{
		if (player->IsShooting == true)
		{
			if (player->IsAiming && player->ItemInInventory != nullptr)
			{
				if (player->ItemInInventory->GetIsTaskItem() == false && player->ItemInInventory->GetIsTake() == true)
				{
					FVector ShootDirection = player->CameraBoom->GetForwardVector();

					player->ItemInInventory->ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					player->ItemInInventory->ItemMesh->SetSimulatePhysics(true);
					player->ItemInInventory->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
					player->ItemInInventory->ItemMesh->AddForce(ShootDirection * 100000 * player->ItemInInventory->ItemMesh->GetMass());
					player->ItemInInventory->SetIsTake(false);
					player->ItemInInventory = nullptr;
					player->IsShooting = false;
					player->NoItem = true;
					_gameHud->GetDefaultWidget()->UpdateItems();
				}
			}
			else
			{
				player->IsShooting = false;
			}
		}
	}
}

#pragma region Pause system

void AStudentCharacter::PauseGame()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	_gameHud->ShowPauseMenu(true);
	_gameHud->ShowDefaultHUD(false);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AStudentCharacter::UnpauseGame()
{
	_gameHud->ShowPauseMenu(false);
	_gameHud->ShowDefaultHUD(true);
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

#pragma endregion 

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
		AAICharacter* ItemHolder = Cast<AAICharacter>(Holder);
		AttachToComponent(ItemHolder->GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Socket_test"));
		ItemHolder->Character = this;
		ItemHolder->Character->IsAiming = false;
		SetInputsState(EnumInputsState::DisableMovement);
		GetMesh()->bPauseAnims = true;

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
	
			PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AStudentCharacter::ItemSystem);

			PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AStudentCharacter::DoAction);
			PlayerInputComponent->BindAction("Action", IE_Released, this, &AStudentCharacter::UndoAction);

			PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AStudentCharacter::Aim);
			PlayerInputComponent->BindAction("Aim", IE_Released, this, &AStudentCharacter::UndoAim);

			PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AStudentCharacter::Shoot);
				
			PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AStudentCharacter::PauseGame);
		}
		case EnumInputsState::DisableMovement :
		{
			PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
			PlayerInputComponent->BindAxis("TurnRate", this, &AStudentCharacter::TurnAtRate);
			PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
			PlayerInputComponent->BindAxis("LookUpRate", this, &AStudentCharacter::LookUpAtRate);
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

