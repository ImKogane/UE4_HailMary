// Fill out your copyright notice in the Description page of Project Settings.


#include "GluePot.h"

AGluePot::AGluePot()
{
	ConstructorHelpers::FObjectFinder<UBlueprint> blueprint_finder(TEXT("Blueprint'/Game/Blueprints/Items/Glue/GlueArea.GlueArea'"));
	GluePuddle = blueprint_finder.Object->GeneratedClass;
}

void AGluePot::Effect(AActor* actor)
{
	Super::Effect(actor);
	GetWorld()->SpawnActor<AActor>(GluePuddle, actor->GetActorLocation(), actor->GetActorRotation());
	this->Destroy();
}
