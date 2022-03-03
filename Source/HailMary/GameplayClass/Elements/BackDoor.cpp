// Fill out your copyright notice in the Description page of Project Settings.


#include "BackDoor.h"

#include "HailMary/Characters/IA_Boss/AICharacter.h"
#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"

void ABackDoor::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	Super::OnBoxOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AStudentCharacter* Player = Cast<AStudentCharacter>(OtherActor);
	if (Player != nullptr)
	{
		NearPlayer = Player;
	}

	AAICharacter* Boss = Cast<AAICharacter>(OtherActor);
	if (Boss != nullptr)
	{
		return;
	}
}

void ABackDoor::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnBoxOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	AStudentCharacter* Player = Cast<AStudentCharacter>(OtherActor);
	if (Player != nullptr)
	{
		NearPlayer = nullptr;
	}

	AAICharacter* Boss = Cast<AAICharacter>(OtherActor);
	if (Boss != nullptr)
	{
		return;
	}
}

void ABackDoor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(NearPlayer != nullptr && PlayerInside != nullptr)
	{
		if(NearPlayer->GetIsDoAction() && ElementProgress <= ElementMaxProgress)
		{
			ElementProgress += NearPlayer->GetMakeTaskSpeed();
				
			FString ProgressString = FString::FromInt(ElementProgress);
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, ProgressString);
				
		}
		else if(ElementProgress > ElementMaxProgress)
		{
			OpenDoor();
		}

	}	
}

bool ABackDoor::GetPlayerIsInside()
{
	if(PlayerInside != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}


/**
 * @brief Open the door if the progress reach 100 percent
 */
void ABackDoor::OpenDoor()
{
	PlayerInside = nullptr;
}