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

void AMerryMaker_BossManager::ActivateSpeaker(AE_SpeakerMM* speaker)
{
	if(!BossBanger && Boss != nullptr)
	{
		ActivesSpeakers.Add(speaker);
		
		FString IntAsString = FString::FromInt(ActivesSpeakers.Num());
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, IntAsString);
		
		if(ActivesSpeakers.Num() == 2)
		{
			Boss->StopBossAura();
			BossBangerMusicComponent->Play();
			BossBanger = true;

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

	FString IntAsString = FString::FromInt(ActivesSpeakers.Num());
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, IntAsString);
	
	if(BossBanger && Boss != nullptr)
	{
		//Stop boss banger music
		BossBangerMusicComponent->Stop();
		BossBanger = false;

		//Re-activate originals sounds
		Boss->PlayBossAura();
		ActivesSpeakers[0]->PlaySpeakerSound();
		
	}
}


