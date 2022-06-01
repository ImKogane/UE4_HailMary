// Fill out your copyright notice in the Description page of Project Settings.


#include "UsableItem_Object.h"
#include "HailMary/Characters/IA_Boss/AICharacter.h"

AUsableItem_Object::AUsableItem_Object()
{
	IsTaskItem = false;
}

void AUsableItem_Object::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	if (OtherActor != nullptr)
	{
		if (OtherActor->IsA(AAICharacter::StaticClass()) || OtherActor->ActorHasTag(TEXT("Ground")))
		{
			if (Cast<AAICharacter>(OtherActor) != nullptr || OtherActor != nullptr)
			{
				Effect(Hit);
			}
		}
	}
}

void AUsableItem_Object::Effect(const FHitResult& Hit)
{
	//Nothing
}

