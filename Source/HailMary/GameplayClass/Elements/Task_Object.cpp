// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_Object.h"

#include "StorageDoor.h"
#include "HailMary/GameplayClass/Items_Objects/TaskItem_Object.h"
#include "HailMary/GameSettings//MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ATask_Object::BeginPlay()
{
	Super::BeginPlay();
	GenerateTask();
	
	//Override Text
	_strDisplayTextLocked = MainNeedItemName->GetItemName() + " / " + OtherNeedItemName->GetItemName();
	//Display locked Text
	_strDisplayText = _strDisplayTextLocked;
	//Get References
	_gameHud = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

}

void ATask_Object::GenerateTask()
{
	int RandIndex = FMath::RandRange(0, TaskStringList. Num()-1);
	Task = TaskStringList[RandIndex];

	ElementName = Task;
}



void ATask_Object::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                     const FHitResult& SweepResult)
{
	Super::OnBoxOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AStudentCharacter* Player = Cast<AStudentCharacter>(OtherActor);
	if (Player == nullptr)
	{
		return; //Overlap actor isn't the player
	}

	if(Player->GetSaveTaskState())
	{
		TaskProgressionLocked = true;
	}
	NearPlayers.Add(Player);
	
	
}

void ATask_Object::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnBoxOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	AStudentCharacter* Player = Cast<AStudentCharacter>(OtherActor);
	if (IsValid(Player))
	{
		//Hide Hud Progress bar
		if(_gameHud)
		{
			_gameHud->GetDefaultWidget()->HideProgressBar(Player->GetPlayerId());
		}
		NearPlayers.Remove(Player);
	}
}

void ATask_Object::Interaction(AActor* Character)
{
	Super::Interaction(Character);


	AStudentCharacter* Player = Cast<AStudentCharacter>(Character);

	if(Player == nullptr) { return; }
	
	if(MainNeedItemName != nullptr && Player->GetItemInInventory() == MainNeedItemName)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Main item good"));
		MainNeedItemName = nullptr;
		Player->ResetInventory();
	}

	if(OtherNeedItemName != nullptr && Player->GetItemInInventory() == OtherNeedItemName)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Other item good"));
		OtherNeedItemName = nullptr;
		Player->ResetInventory();
	}

	if(MainNeedItemName == nullptr && OtherNeedItemName == nullptr && !TaskUnlocked)
	{
		UnlockTask();
	}
}

void ATask_Object::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(TaskUnlocked && !TaskCompleted)
	{
		for (AStudentCharacter* Player : NearPlayers)
		{
			if(Player->GetIsDoAction() && ElementProgress <= ElementMaxProgress)
			{
				ElementProgress += Player->GetMakeTaskSpeed();
				
				//Update Hud Progress bar
				if(_gameHud)
				{
					_gameHud->GetDefaultWidget()->SetProgressBarValue(Player->GetPlayerId(),ElementProgress);
				}

				ElementInteractionCount++;
			}
			else
			{
				if(ElementProgress > ElementMaxProgress)
				{
					CompleteTask();
				}
				
				//Hide Hud Progress bar
				if(_gameHud)
				{
					_gameHud->GetDefaultWidget()->HideProgressBar(Player->GetPlayerId());
				}
			}
		}

		if(ElementInteractionCount == 0 && !TaskProgressionLocked)
		{
			if(ElementProgress > 0)
			{
				ElementProgress -= DecreaseRate;
			}
			
		}
		
		ElementInteractionCount = 0;

	}	
}


/**
 * @brief Unlock the task if the 2 needed items are completed
 */
void ATask_Object::UnlockTask()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Task unlock"));
	TaskUnlocked = true;
	_strDisplayText = _strDisplayTextUnlocked;
	if(_gameHud )
	{
		_gameHud->GetDefaultWidget()->UpdateDisplayText();
	}
}

/**
 * @brief Complete the task if the task is unlocked and the progress reach 100 percent
 */
void ATask_Object::CompleteTask()
{
	TaskCompleted = true;
	//TheGameInstance->GetPlayCycle()->ResetTimer();
	
	if(StorageDoor != nullptr) StorageDoor->OpenDoor();
	_strDisplayText = _strDisplayTextCompleted;
	
	if(_gameHud )
	{
		_gameHud->GetDefaultWidget()->UpdateDisplayText();
	}
}
