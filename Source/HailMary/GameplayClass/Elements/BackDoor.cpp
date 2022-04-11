// Fill out your copyright notice in the Description page of Project Settings.


#include "BackDoor.h"

#include "Components/AudioComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HailMary/MainGameInstance.h"
#include "HailMary/Characters/IA_Boss/AICharacter.h"
#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"
#include "Kismet/GameplayStatics.h"

ABackDoor::ABackDoor()
{
	_sceneComponentTeleportPosition = CreateDefaultSubobject<USceneComponent>("Teleport Position");
	_sceneComponentTeleportPosition->SetupAttachment(ElementMesh);
	
	_sceneComponentEntrancePosition= CreateDefaultSubobject<USceneComponent>("Entrance Position");
	_sceneComponentEntrancePosition->SetupAttachment(ElementMesh);

	_cameraComponent= CreateDefaultSubobject<UCameraComponent>("Camera");
	_cameraComponent->SetupAttachment(ElementMesh);

	_audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("audioCue"));
	_audioComponent->SetupAttachment(RootComponent);
}

void ABackDoor::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	Super::OnBoxOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AStudentCharacter* Player = Cast<AStudentCharacter>(OtherActor);
	if (Player != nullptr)
	{
		_arrNearPlayer.Add(Player);
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
	if (IsValid(Player))
	{
		//Reset Progress
		ElementProgress = 0;
		//Hide Hud Progress bar
		if(_gameHud)
		{
			_gameHud->GetDefaultWidget()->HideProgressBar(Player->GetPlayerId());
		}
		//Clear reference
		_arrNearPlayer.Remove(Player);
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
	
	if(_arrNearPlayer.Num()>0 && PlayerInside != nullptr)
	{
		for ( AStudentCharacter* l_currentPlayer: _arrNearPlayer)
		{
			if(l_currentPlayer != PlayerInside)
			{
				if(l_currentPlayer->GetIsDoAction() && ElementProgress <= ElementMaxProgress)
				{
					ElementProgress += l_currentPlayer->GetMakeTaskSpeed();
					//Update Hud Progress bar
					if(_gameHud)
					{
						_gameHud->GetDefaultWidget()->SetProgressBarValue(l_currentPlayer->GetPlayerId(),ElementProgress);
					}
					//Debug
					// FString ProgressString = FString::FromInt(ElementProgress);
					// GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, ProgressString);
				}
				else
				{
					if(ElementProgress > ElementMaxProgress)
					{
						OpenDoor();
					}
					else if( ElementProgress > 0)
					{
						ElementProgress -= l_currentPlayer->GetMakeTaskSpeed();
					}
					//Hide Hud Progress bar
					if(_gameHud)
					{
						_gameHud->GetDefaultWidget()->HideProgressBar(l_currentPlayer->GetPlayerId());
					}
				}
			}
		}
	}	
}

void ABackDoor::SetPlayerInside(AStudentCharacter* player)
{
	//Port Player
	FVector vecLocation = this->GetTeleportPosition();
	player->TeleportTo(vecLocation, GetActorRotation());
	//Inputs
	player->SetInputsState(EnumInputsState::DisableMovementAndCamera);
	player->SetActorRotation(this->GetCameraComponent()->GetComponentRotation());
	//Camera
	player->CameraBoom->Deactivate();
	player->FollowCamera->SetWorldLocation(this->GetCameraComponent()->GetComponentLocation());
	player->FollowCamera->SetWorldRotation(this->GetCameraComponent()->GetComponentRotation());
	
	if( PlayerInside == nullptr)
	{
		PlayerInside = player;
	}

	_gameInstance->AddLockedPlayer(player);
	
	if( _gameInstance->GetnbLockedPlayer() > 1)
	{
		//Someone already locked somewhere : Game Over
		UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false); //Restart level
	}
}

void ABackDoor::Interaction(AActor* character)
{
	Super::Interaction(character);

	AStudentCharacter* l_studentCharacter = Cast<AStudentCharacter>(character);
	if(PlayerInside == l_studentCharacter)
	{
		//Play cue
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Play Cue"));
		if(_audioComponent)
		{
			_audioComponent->Play();
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
	//Port Player outside
	FVector l_vecLocation = GetEntrancePosition();
	PlayerInside->TeleportTo(l_vecLocation, GetActorRotation(),false,true);
	//Enable back Inputs
	PlayerInside->SetInputsState(EnumInputsState::EnableAll);
	PlayerInside->SetActorRotation(this->GetCameraComponent()->GetComponentRotation());
	//Reset Camera
	PlayerInside->FollowCamera->ResetRelativeTransform();
	PlayerInside->CameraBoom->Activate();

	//Reset
	if( _gameInstance && IsValid(PlayerInside))
	{
		_gameInstance->RemoveLockedPlayer(PlayerInside);
	}
	PlayerInside = nullptr;
	ElementProgress = 0;
}