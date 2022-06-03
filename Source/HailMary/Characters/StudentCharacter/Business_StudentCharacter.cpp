// Fill out your copyright notice in the Description page of Project Settings.


#include "Business_StudentCharacter.h"


void ABusiness_StudentCharacter::BeginPlay()
{
	Super::BeginPlay();

	MakeTaskSpeed = MakeTaskSpeed * TaskSpeedBoost;
}


