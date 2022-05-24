// Fill out your copyright notice in the Description page of Project Settings.


#include "ReversibleProps.h"

#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"

void AReversibleProps::Interaction(AActor* Character)
{
	Super::Interaction(Character);
	
	AStudentCharacter* Player = Cast<AStudentCharacter>(Character);

	if(Player == nullptr) { return; }

	IsFalling = true;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Falling ..."));	
}

