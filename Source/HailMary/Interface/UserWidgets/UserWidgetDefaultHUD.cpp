// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetDefaultHUD.h"

#include "Components/TextBlock.h"
#include "HailMary/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UUserWidgetDefaultHUD::GetReferences()
{
	gameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	m_player1 = Cast<AStudentCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetCharacter());
	m_player2 = Cast<AStudentCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 1)->GetCharacter());
}

void UUserWidgetDefaultHUD::UpdateWidget()
{
	FString txtTimer = TEXT("Time left : ") + gameInstance->GetPlayCycle()->GetTimer();;
	textTimer->SetText(FText::FromString(txtTimer));
	
	FString txtTaskCount = TEXT("Taches réaliser : ") + FString::FromInt(gameInstance->GetTaskCount());
	textTaskCount->SetText(FText::FromString(txtTaskCount));

	if(m_player1)
	{
		FString txtItemPlayer1= "Empty";
		if(IsValid(m_player1->GetItemInInventory()))
		{
			txtItemPlayer1 = m_player1->GetItemInInventory()->GetItemName();
		}
		textItemPlayer1->SetText(FText::FromString(txtItemPlayer1));
	}


	if(m_player2)
	{
		FString txtItemPlayer2= "_ _ _";
		if(IsValid(m_player2->GetItemInInventory()))
		{
			txtItemPlayer2 = m_player2->GetItemInInventory()->GetItemName();
		}
		textItemPlayer2->SetText(FText::FromString(txtItemPlayer2));
	}
}
