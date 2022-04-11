// Fill out your copyright notice in the Description page of Project Settings.


#include "HidingSpot.h"

#include "GameFramework/SpringArmComponent.h"
#include "HailMary/MainGameInstance.h"
#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"
#include "Kismet/GameplayStatics.h"


AHidingSpot::AHidingSpot()
{
	//(ACharacter::CapsuleComponentName
	_sceneComponentTeleportPosition = CreateDefaultSubobject<USceneComponent>("sceneComponent");
	_sceneComponentTeleportPosition->SetupAttachment(ElementMesh);

	_cameraComponent= CreateDefaultSubobject<UCameraComponent>("Camera");
	_cameraComponent->SetupAttachment(ElementMesh);
}

void AHidingSpot::BeginPlay()
{
	Super::BeginPlay();

	//Get references
	gameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	//Find all Hiding Spots
	TArray<AActor*> arrHidingSpotsActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AHidingSpot::StaticClass(),arrHidingSpotsActors );
	for (AActor* hidingSpotActor : arrHidingSpotsActors)
	{
		AHidingSpot* currentHidingSpot = Cast<AHidingSpot>(hidingSpotActor);
		if( IsValid(currentHidingSpot))
		{
			_arrHidingSpots.Add(currentHidingSpot);
		}
	}
}

void AHidingSpot::Interaction(AActor* character)
{
	Super::Interaction(character);

	AStudentCharacter* l_studentCharacter = Cast<AStudentCharacter>(character);
	if( IsValid(l_studentCharacter))
	{
		EnterLocker(l_studentCharacter);
	}
}

void AHidingSpot::EnterLocker(AStudentCharacter* studentCharacter)
{
	if(!_bContainPlayer)
	{
		//debug
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Enter Locker"));
		
		//Do once
		_bContainPlayer = true;
		
		//Port player into the locker
		if( IsValid(_sceneComponentTeleportPosition) && studentCharacter)
		{
			//Inputs
			studentCharacter->SetInputsState(EnumInputsState::DisableAll);
			//Player position & rotation
			studentCharacter->SetActorLocation(_sceneComponentTeleportPosition->GetComponentLocation());
			studentCharacter->SetActorRotation(_cameraComponent->GetComponentRotation());
			//Camera
			studentCharacter->CameraBoom->Deactivate();
			studentCharacter->FollowCamera->SetWorldLocation(_cameraComponent->GetComponentLocation());
			studentCharacter->FollowCamera->SetWorldRotation(_cameraComponent->GetComponentRotation());
			//Hide Hud Progress Interaction text
			SetHudEnable(false);
		}

		//Add Locked Player To GameInstance
		_gameInstance->AddLockedPlayer(studentCharacter);
		if( _gameInstance->GetnbLockedPlayer() > 1)
		{
			gameInstance->GetPlayCycle()->ResetTimer();
			//Someone already locked somewhere : Game Over
			UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false); //Restart level
		}
	}
}

void AHidingSpot::ResetLocker()
{
	_bContainPlayer = false;
}

void AHidingSpot::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBoxOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AStudentCharacter* Player = Cast<AStudentCharacter>(OtherActor);
	if (Player != nullptr)
	{
		//Do smth
	}
}

void AHidingSpot::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnBoxOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
