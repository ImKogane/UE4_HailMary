// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayCycle.h"

#include "MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayCycle::APlayCycle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayCycle::BeginPlay()
{
	Super::BeginPlay();

	LoopTime = InitialLoopTime;
	GetWorldTimerManager().SetTimer(GameTimer, this, &APlayCycle::Clock, 1.0f, true);
	
	TheGameInstance = Cast<UMainGameInstance>(GetGameInstance());
	TheGameInstance->SetPlayCycle(this);
	TheGameInstance->ResetInstance();
}

// Called every frame
void APlayCycle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Loop();
	
}

FString APlayCycle::GetTimer()
{
	int TimeSeconds = LoopTime % 60;
	int TimeMinuts = LoopTime / 60;
	FString Timer = FString::FromInt(TimeMinuts) + ":" + FString::FromInt(TimeSeconds);
	return  Timer;
}


void APlayCycle::Loop()
{	
	if (LoopTime <= 0)
	{
		ResetTimer();
	}
}

void APlayCycle::Clock()
{
	if (LoopTime > 0)
	{
		LoopTime--;
//		ShowTimer();
	}
	else
	{
		GetWorldTimerManager().ClearTimer(GameTimer);
	}
}

void APlayCycle::ShowTimer()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, GetTimer());
}

void APlayCycle::ResetTimer()
{
	//Reset Level
	UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
	UMainGameInstance* l_gameInstance = Cast<UMainGameInstance>(GetGameInstance());
	l_gameInstance->ResetInstance();
	//Reset Timer
	GetWorldTimerManager().ClearTimer(GameTimer);
	LoopTime = InitialLoopTime;
	GetWorldTimerManager().SetTimer(GameTimer, this, &APlayCycle::Clock, 1.0f, true);
}

void APlayCycle::StopTimer()
{
	
}
