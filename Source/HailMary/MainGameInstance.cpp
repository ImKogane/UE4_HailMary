// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

#include "Kismet/GameplayStatics.h"

void UMainGameInstance::Init()
{
	Super::Init();
	playCycle = Cast<APlayCycle>(UGameplayStatics::GetActorOfClass(GetWorld(),APlayCycle::StaticClass()));
}

void UMainGameInstance::ResetInstance()
{
	TaskCount = 0;
}
