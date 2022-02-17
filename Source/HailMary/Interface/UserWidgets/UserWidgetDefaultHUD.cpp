// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetDefaultHUD.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "HailMary/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"

void UUserWidgetDefaultHUD::GetReferences()
{
	gameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	m_player1 = Cast<AStudentCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetCharacter());
	m_player2 = Cast<AStudentCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 1)->GetCharacter());

	HideInteractPlayer1();
	HideInteractPlayer2();
}

void UUserWidgetDefaultHUD::UpdateWidget()
{
	FString txtTimer = TEXT("Time left : ") + gameInstance->GetPlayCycle()->GetTimer();;
	textTimer->SetText(FText::FromString(txtTimer));
	
	FString txtTaskCount = TEXT("Task Done : ") + FString::FromInt(gameInstance->GetTaskCount());
	textTaskCount->SetText(FText::FromString(txtTaskCount));
	
	UpdateItems();
	UpdatePerks();
}

void UUserWidgetDefaultHUD::UpdatePerks()
{
	if(m_player1)
	{
		//First Perk Icon
		UTexture2D* FirstPerkTexture = nullptr;
		if(IsValid(m_player1->GetFirstPerk()))
		{
			FirstPerkTexture = m_player1->GetFirstPerk()->GetTextureIcon();
		}
		imgPerk1Player1->SetBrushFromTexture(FirstPerkTexture, false);
		//Second Perk Icon
		UTexture2D* SecondPerkTexture = nullptr;
		if(IsValid(m_player1->GetSecondPerk()))
		{
			SecondPerkTexture = m_player1->GetSecondPerk()->GetTextureIcon();
		}
		imgPerk2Player1->SetBrushFromTexture(SecondPerkTexture, false);
	}

	if(m_player2)
	{
		//First Perk Icon
		UTexture2D* FirstPerkTexture = nullptr;
		if(IsValid(m_player2->GetFirstPerk()))
		{
			FirstPerkTexture = m_player2->GetFirstPerk()->GetTextureIcon();
		}
		imgPerk1Player2->SetBrushFromTexture(FirstPerkTexture, false);
		//Second Perk Icon
		UTexture2D* SecondPerkTexture = nullptr;
		if(IsValid(m_player2->GetSecondPerk()))
		{
			SecondPerkTexture = m_player2->GetSecondPerk()->GetTextureIcon();
		}
		imgPerk2Player2->SetBrushFromTexture(SecondPerkTexture, false);
	}
}

void UUserWidgetDefaultHUD::UpdateItems()
{
	if(m_player1)
	{
		//Item Txt
		FString txtItemPlayer1= "Empty";
		if(IsValid(m_player1->GetItemInInventory()))
		{
			txtItemPlayer1 = m_player1->GetItemInInventory()->GetItemName();
		}
		textItemPlayer1->SetText(FText::FromString(txtItemPlayer1));
		//Item Icon
		UTexture2D* texture = textureItemEmpty;
		if(IsValid(m_player1->GetItemInInventory()))
		{
			texture = m_player1->GetItemInInventory()->GetItemArtwork();
		}
		imgItemPlayer1->SetBrushFromTexture(texture, false);
	}


	if(m_player2)
	{
		//Item Txt
		FString txtItemPlayer2= "Empty";
		if(IsValid(m_player2->GetItemInInventory()))
		{
			txtItemPlayer2 = m_player2->GetItemInInventory()->GetItemName();
		}
		textItemPlayer2->SetText(FText::FromString(txtItemPlayer2));
		//Item Icon
		UTexture2D* texture = textureItemEmpty;
		if(IsValid(m_player2->GetItemInInventory()))
		{
			texture = m_player2->GetItemInInventory()->GetItemArtwork();
		}
		imgItemPlayer2->SetBrushFromTexture(texture, false);
	}
}

void UUserWidgetDefaultHUD::ShowInteractPlayer1()
{
	widgetInteractPlayer1->SetVisibility(ESlateVisibility::Visible);
}

void UUserWidgetDefaultHUD::ShowInteractPlayer2()
{
	widgetInteractPlayer2->SetVisibility(ESlateVisibility::Visible);
}

void UUserWidgetDefaultHUD::HideInteractPlayer1()
{
	widgetInteractPlayer1->SetVisibility(ESlateVisibility::Hidden);
}

void UUserWidgetDefaultHUD::HideInteractPlayer2()
{
	widgetInteractPlayer2->SetVisibility(ESlateVisibility::Hidden);
}

void UUserWidgetDefaultHUD::SetTextInteractPlayer1(FString newText)
{
	FText NewText = FText::FromString(newText);
	widgetInteractPlayer1->textInteract->SetText(NewText) ;
}

void UUserWidgetDefaultHUD::SetTextInteractPlayer2(FString newText)
{
	FText NewText = FText::FromString(newText);
	widgetInteractPlayer2->textInteract->SetText(NewText) ;
}
