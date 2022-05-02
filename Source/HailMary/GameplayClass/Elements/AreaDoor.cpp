// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaDoor.h"

#include "Components/BoxComponent.h"
#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"
#include "HailMary/GameplayClass/Items_Objects/KeyItem_Object.h"

// Sets default values
AAreaDoor::AAreaDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AAreaDoor::Interaction(AActor* Character)
{
	Super::Interaction(Character);
	AStudentCharacter* student = Cast<AStudentCharacter>(Character);

	if(student != nullptr)
	{
		AKeyItem_Object* key = Cast<AKeyItem_Object>(student->GetItemInInventory());

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("Key "));
		if(key != nullptr && key->GetKeyArea() == Area)
		{
			OpenDoor();
		}
	}
}

// Called when the game starts or when spawned
void AAreaDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAreaDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAreaDoor::OpenDoor()
{
	Destroy(true);
}

