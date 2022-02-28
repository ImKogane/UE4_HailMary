// Fill out your copyright notice in the Description page of Project Settings.


#include "HidingSpot.h"

#include "HailMary/MainGameInstance.h"
#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"
#include "Kismet/GameplayStatics.h"


AHidingSpot::AHidingSpot()
{
	//(ACharacter::CapsuleComponentName
	_sceneComponentTeleportPosition = CreateDefaultSubobject<USceneComponent>("sceneComponent");
	_sceneComponentTeleportPosition->SetupAttachment(RootComponent);
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

void AHidingSpot::Interaction(AStudentCharacter* studentCharacter)
{
	Super::Interaction(studentCharacter);
	if( IsValid(studentCharacter))
	{
		EnterLocker(studentCharacter);
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
			studentCharacter->SetActorLocation(_sceneComponentTeleportPosition->GetComponentLocation());
		}

		//Check if the other player is in a locker too ?
		for (AHidingSpot* hidingSpot: _arrHidingSpots)
		{
			if(hidingSpot->GetContainPlayer() && hidingSpot != this)
			{
				//Si les deux joueur entrent, met fin au cycle actuel
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("Should end cycle"));
				if( IsValid(gameInstance))
				{
					gameInstance->GetPlayCycle()->ResetTimer();
					UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
				}
			}
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
