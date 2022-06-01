// Fill out your copyright notice in the Description page of Project Settings.


#include "GluePot.h"

AGluePot::AGluePot()
{
}

void AGluePot::BeginPlay()
{
	Super::BeginPlay();
}

void AGluePot::Effect(const FHitResult& Hit)
{
	Super::Effect(Hit);
	if(IsValid(_bpGlueArea))
	{
		FRotator zero = { 0,0,0 };
		GetWorld()->SpawnActor<AActor>(_bpGlueArea, Hit.Location, zero);
	}
	this->Destroy();
}
