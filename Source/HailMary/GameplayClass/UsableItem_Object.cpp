// Fill out your copyright notice in the Description page of Project Settings.


#include "UsableItem_Object.h"
#include "HailMary/Characters/IA_Boss/AICharacter.h"

AUsableItem_Object::AUsableItem_Object()
{
	IsTaskItem = false;
}

void AUsableItem_Object::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBoxOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor->IsA(AAICharacter::StaticClass()) || OtherActor->ActorHasTag(TEXT("Ground")))
	{
		if (Cast<AAICharacter>(OtherActor) != nullptr || OtherActor != nullptr)
		{
			Effect(OtherActor);
		}
	}
}

void AUsableItem_Object::Effect(AActor* actor)
{
	//Nothing
}

