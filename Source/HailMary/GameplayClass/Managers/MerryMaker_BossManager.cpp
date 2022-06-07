// Fill out your copyright notice in the Description page of Project Settings.

#include "HailMary/GameplayClass/Managers/MerryMaker_BossManager.h"

#include "Components/AudioComponent.h"
#include "HailMary/Characters/IA_Boss/AICharacter.h"
#include "HailMary/GameplayClass/Elements/E_SpeakerMM.h"

// Sets default values
AMerryMaker_BossManager::AMerryMaker_BossManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Banger music component
	BossBangerMusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BossMusic"));
	BossBangerMusicComponent->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AMerryMaker_BossManager::BeginPlay()
{
	Super::BeginPlay();
	BossBangerMusicComponent->Stop();
	
}

// Called every frame
void AMerryMaker_BossManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMerryMaker_BossManager::ActivateSpeaker(AE_SpeakerMM* aSpeaker)
{
	if(!BossBanger)
	{
		ActivesSpeakers.Add(aSpeaker);
		
		if(ActivesSpeakers.Num() == 2)
		{
			if(Boss != nullptr) Boss->StopBossAura();

			//Activate boss banger music
			BossBangerMusicComponent->Play();
			BossBanger = true;

			//Stop all speaker sounds
			for (AE_SpeakerMM* speaker : ActivesSpeakers)
			{
				speaker->StopSpeakerSound();
			}
		}
	}
}

void AMerryMaker_BossManager::DesactivateSpeaker(AE_SpeakerMM* speaker)
{
	ActivesSpeakers.Remove(speaker);
	
	if(BossBanger)
	{
		//Stop boss banger music
		BossBangerMusicComponent->Stop();
		BossBanger = false;

		//Re-activate originals sounds
		if(Boss != nullptr) Boss->PlayBossAura();
		ActivesSpeakers[0]->PlaySpeakerSound();
	}
}


