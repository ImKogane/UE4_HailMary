// Fill out your copyright notice in the Description page of Project Settings.


#include "GluePot.h"

AGluePot::AGluePot()
{
}

void AGluePot::BeginPlay()
{
	Super::BeginPlay();
}

void AGluePot::Effect(AActor* actor)
{
	Super::Effect(actor);
	if(IsValid(_bpGlueArea))
	{
		GetWorld()->SpawnActor<AActor>(_bpGlueArea, actor->GetActorLocation(), actor->GetActorRotation());
	}
	this->Destroy();
}
