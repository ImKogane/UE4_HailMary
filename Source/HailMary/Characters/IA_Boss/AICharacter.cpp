﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "MyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HailMary/GameplayClass/ExitDoor.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AAICharacter::AAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initializing the pawn sensing component
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	//Set the peripheral vision angle to 90 degrees
	PawnSensingComp->SetPeripheralVisionAngle(90.f);
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	//Get references
	 AIController = Cast<AMyAIController>(GetController());
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AExitDoor::StaticClass(), m_arrDoors);
	
	//Register the function that is going to fire when the character sees a Pawn
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAICharacter::OnSeePlayer);
	}

	
}

AActor* AAICharacter::GetNearestDoor()
{
	if(m_arrDoors.Num()>0 )
	{
		float fNearestDoorDist = -1;
		for (AActor*  currentDoor : m_arrDoors)
		{
			float fDistance = FVector::Dist(this->GetActorLocation(),currentDoor->GetActorLocation());
			if(fDistance < fNearestDoorDist || fNearestDoorDist == -1) // si la nouvelle distance est plus courte
			{
				NearestDoor = currentDoor;
				fNearestDoorDist = fDistance;
			}
		}
		return NearestDoor;
	}
	return nullptr;
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// AMyAIController* AIController = Cast<AMyAIController>(GetController());
	if(bAIVisible == true)
	{
		if((GetWorld()->TimeSeconds - LastSeenTime) > TimeOut)
		{
			AIController->SetNotSeenTarget();
		}
	}
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAICharacter::OnSeePlayer(APawn* InPawn)
{
	//AMyAIController* AIController = Cast<AMyAIController>(GetController());
	//Set the seen target on the blackboard
	if (AIController)
	{
		AIController->StopMovement();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Je te vois"));
		GetCharacterMovement()->MaxWalkSpeed = 400;
		LastSeenTime = GetWorld()->GetTimeSeconds();
		AIController->SetSeenTarget(InPawn);
	}
}

void AAICharacter::Pick()
{
	 if(IsValid(AIController))
	 {
	 	if(IsValid(Character))
	 	{
	 		Character->GrabPlayer(this);
	 		GetCharacterMovement()->MaxWalkSpeed = 250;
	 		AIController->SetIsHoldingPlayer(true);
	 	}
	 }
}