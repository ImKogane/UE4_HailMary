// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaDoor.h"

#include "Components/BoxComponent.h"
#include "HailMary/GameSettings/MainGameInstance.h"
#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"
#include "HailMary/GameplayClass/Items_Objects/KeyItem_Object.h"
#include "Kismet/GameplayStatics.h"

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
		
		if(key != nullptr && key->GetKeyArea() == Area)
		{
			student->ResetInventory();
			OpenDoor();
		}
	}
}

// Called when the game starts or when spawned
void AAreaDoor::BeginPlay()
{
	Super::BeginPlay();

	TheGameInstance = Cast<UMainGameInstance>(GetGameInstance());
	_gameHud = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
}


void AAreaDoor::OpenDoor()
{
	
	TheGameInstance->AddTaskCount(1);
	
	if(_gameHud )
	{
		_gameHud->GetDefaultWidget()->UpdateDisplayText();
		_gameHud->GetDefaultWidget()->UpdateTasks();
	}
	
	Destroy(true);
}

