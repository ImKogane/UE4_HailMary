// Fill out your copyright notice in the Description page of Project Settings.


#include "E_SpeakerMM.h"

#include "Components/AudioComponent.h"
#include "HailMary/GameplayClass/Managers/MerryMaker_BossManager.h"

AE_SpeakerMM::AE_SpeakerMM()
{
	SpeakerAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SpeakerAudio"));
	SpeakerAudioComponent->SetupAttachment(BaseComponent);
}

void AE_SpeakerMM::BeginPlay()
{
	Super::BeginPlay();
	StopSpeakerSound();
}


void AE_SpeakerMM::Interaction(AStudentCharacter* studentCharacter)
{
	Super::Interaction(studentCharacter);

	if(!IsActivate)
	{
		PlaySpeakerSound();
		IsActivate = true;
		_strDisplayText = "Press E to stop speaker";
		MerryMakerManager->ActivateSpeaker(this);
	}
	else
	{
		StopSpeakerSound();
		IsActivate = false;
		MerryMakerManager->DesactivateSpeaker(this);
		_strDisplayText = "Press E to activate speaker";
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
