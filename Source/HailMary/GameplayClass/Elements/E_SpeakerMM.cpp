// Fill out your copyright notice in the Description page of Project Settings.


#include "E_SpeakerMM.h"

#include "Components/AudioComponent.h"
#include "HailMary/Characters/IA_Boss/AICharacter.h"
#include "HailMary/GameplayClass/Managers/MerryMaker_BossManager.h"

AE_SpeakerMM::AE_SpeakerMM()
{
	//Speaker music component
	SpeakerAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SpeakerAudio"));
	SpeakerAudioComponent->SetupAttachment(BaseComponent);

	_sceneComponentEntrancePosition= CreateDefaultSubobject<USceneComponent>("Entrance Position");
	_sceneComponentEntrancePosition->SetupAttachment(ElementMesh);
}

void AE_SpeakerMM::BeginPlay()
{
	Super::BeginPlay();
	StopSpeakerSound();
}


void AE_SpeakerMM::Interaction(AActor* Character)
{
	Super::Interaction(Character);

	//If the Boss Activate the Bass
	AAICharacter* MerryMaker = Cast<AAICharacter>(Character);
	if(IsValid(MerryMaker))
	{
		//Just activate
		PlaySpeakerSound();
		_bIsActivate = true;
		_strDisplayText = "Press E to stop speaker";
		MerryMakerManager->ActivateSpeaker(this);
	}

	//If the Player Activate the banger
	AStudentCharacter* studentCharacter = Cast<AStudentCharacter>(Character);
	if(IsValid(studentCharacter))
	{
		//Toggle
		if(!_bIsActivate)
		{
			PlaySpeakerSound();
			_bIsActivate = true;
			_strDisplayText = "Press E to stop speaker";
			MerryMakerManager->ActivateSpeaker(this);
		}
		else
		{
			StopSpeakerSound();
			_bIsActivate = false;
			MerryMakerManager->DesactivateSpeaker(this);
			_strDisplayText = "Press E to activate speaker";
		}
	}
}

void AE_SpeakerMM::PlaySpeakerSound()
{
	SpeakerAudioComponent->Play();
}

void AE_SpeakerMM::StopSpeakerSound()
{
	SpeakerAudioComponent->Stop();
}
