// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "MyAIController.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HailMary/GameplayClass/Elements/BackDoor.h"
#include "HailMary/GameplayClass/Elements/E_SpeakerMM.h"
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

	BossAuraAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BossAura"));
	BossAuraAudioComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	//Get references
	 AIController = Cast<AMyAIController>(GetController());
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ABackDoor::StaticClass(), m_arrDoors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AE_SpeakerMM::StaticClass(), m_arrMerryMaker);
	_gameHud = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	
	//Register the function that is going to fire when the character sees a Pawn
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAICharacter::OnSeePlayer);
	}

	//Setup Values
	APlayerController* l_playerController = UGameplayStatics::GetPlayerController(this, 0);
	AStudentCharacter* l_studentCharacter = Cast<AStudentCharacter>(l_playerController->GetCharacter());
	_fDefaultSpeed = GetCharacterMovement()->GetMaxSpeed();
	_fRunningSpeed = l_studentCharacter->GetRunningSpeed() * _fPlayerSeenSpeedMultiplicator;
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

AActor* AAICharacter::GetNearestMerryMaker()
{
	if(m_arrMerryMaker.Num()>0 )
	{
		float fNearestMerryMakerDist = -1;
		for (AActor*  currentMerryMaker : m_arrMerryMaker)
		{
			float fDistance = FVector::Dist(this->GetActorLocation(),currentMerryMaker->GetActorLocation());
			if(fDistance < fNearestMerryMakerDist || fNearestMerryMakerDist == -1) // si la nouvelle distance est plus courte
				{
				NearestMerryMaker = currentMerryMaker;
				fNearestMerryMakerDist = fDistance;
				}
		}
		return NearestMerryMaker;
	}
	return nullptr;
}


// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//AMyAIController* AIController = Cast<AMyAIController>(GetController());
	if(bAIVisible == true)
	{
		if((GetWorld()->TimeSeconds - LastSeenTime) > m_fTimeOut)
		{
			AIController->SetNotSeenTarget();
			//Reset Speed
			GetCharacterMovement()->MaxWalkSpeed = _fRunningSpeed;
		}
	}
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAICharacter::PlayBossAura()
{
	BossAuraAudioComponent->Play();
}

void AAICharacter::StopBossAura()
{
	BossAuraAudioComponent->Stop();
}

void AAICharacter::OnSeePlayer(APawn* InPawn)
{
	//Set the seen target on the blackboard
	if (AIController)
	{
		//Stop if target changed
		if(!IsValid(AIController->GetBlackboardComp()->GetValueAsObject(AIController->GetTargetKey())))
		{
			AIController->StopMovement();
		}
		
		//Default behavior
		GetCharacterMovement()->MaxWalkSpeed = _fRunningSpeed;
		LastSeenTime = GetWorld()->GetTimeSeconds();
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Je te vois "));
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
	 		AIController->SetIsHoldingPlayer(true);
	 	}
	 }
}

void AAICharacter::Drop()
{
	if(IsValid(AIController))
	{
		if(IsValid(Character))
		{
			Character->DropPlayer();
			GetCharacterMovement()->MaxWalkSpeed = _fDefaultSpeed;

			//Port player to the other side if the dooor
			ABackDoor* backDoorNearest = Cast<ABackDoor>(GetNearestDoor());
			if(IsValid(backDoorNearest))
			{
				backDoorNearest->SetPlayerInside(Character);
				Character = nullptr;
			}
			
			AIController->SetIsHoldingPlayer(false);
			AIController->SetNotSeenTarget();
		}
	}
}
