// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitDoor.h"

#include "HailMary/GameSettings//MainGameInstance.h"
#include "HailMary/GameSettings/HailMaryGameMode.h"
#include "Kismet/GameplayStatics.h"

void AExitDoor::BeginPlay()
{
	Super::BeginPlay();

	TheGameInstance = Cast<UMainGameInstance>(GetGameInstance());
	_gameHud = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

}


void AExitDoor::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                     const FHitResult& SweepResult)
{
	Super::OnBoxOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AStudentCharacter* Player = Cast<AStudentCharacter>(OtherActor);
	if (Player == nullptr)
	{
		return; //Overlap actor isn't the player
	}

	NearPlayer = Player;
}

void AExitDoor::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnBoxOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	AStudentCharacter* Player = Cast<AStudentCharacter>(OtherActor);
	if (Player == nullptr)
	{
		return; //Overlap actor isn't the player
	}
	NearPlayer = nullptr;
}

void AExitDoor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(!IsOpen && NearPlayer != nullptr && TheGameInstance->GetTaskCount() >= 4)
	{
			if(NearPlayer->GetIsDoAction() && ElementProgress <= ElementMaxProgress)
			{
				IsOpening = true;
				ElementProgress += NearPlayer->GetOpenDoorSpeed();
				
				if(_gameHud)
				{
					_gameHud->GetDefaultWidget()->SetProgressBarValue(NearPlayer->GetPlayerId(),ElementProgress);
				}
				

			}
			else
			{
				IsOpening = false;
				
				if(ElementProgress > ElementMaxProgress)
				{
					OpenDoor();
				}

				//Hide Hud Progress bar
				if(_gameHud)
				{
					_gameHud->GetDefaultWidget()->HideProgressBar(NearPlayer->GetPlayerId());
				}
			}

	}	
}


/**
 * @brief Open the dooor if the progress reach 100 percent
 */
void AExitDoor::OpenDoor()
{
	IsOpen = true;
	TheGameInstance->SetDoorIsOpen(true);

	AHailMaryGameMode* gamemode = Cast<AHailMaryGameMode>(GetWorld()->GetAuthGameMode());
	if(gamemode != nullptr)
	{
		gamemode->WinGame();
	}
}