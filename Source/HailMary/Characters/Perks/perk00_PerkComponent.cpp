// Fill out your copyright notice in the Description page of Project Settings.


#include "perk00_PerkComponent.h"

#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"

void Uperk00_PerkComponent::UsePerk()
{
	Super::UsePerk();

	AStudentCharacter* player = Cast<AStudentCharacter>(this->GetOwner());

	if(player != nullptr)
	{
		player->SetSaveTaskState(true);
	}

	
}
