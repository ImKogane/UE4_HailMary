// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetDefaultHUD.h"

//#include "ToolBuilderUtil.h"
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

void UUserWidgetDefaultHUD::PostStart()
{
	bPostStartDone = true;
	UpdatePerks(); // To Do once BOTH player have been Instantiated
	UpdateTasks(); // Same then previous && When a task got completed
	HideProgressBar(1);
	HideProgressBar(2);
}

void UUserWidgetDefaultHUD::CheckPostStart()
{
	if( !bPostStartDone)
	{
		TArray<AActor*> arrPlayer;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(),AStudentCharacter::StaticClass(), arrPlayer);
		if(arrPlayer.Num() >= 2 )
		{
			PostStart();
		}
	}
}

void UUserWidgetDefaultHUD::UpdateWidget()
{
	CheckPostStart();
	UpdateTimer();
}

void UUserWidgetDefaultHUD::UpdateTimer()
{
	FString txtTimer = TEXT("Time left : ") + gameInstance->GetPlayCycle()->GetTimer();;
	textTimer->SetText(FText::FromString(txtTimer));
}

void UUserWidgetDefaultHUD::UpdateTasks()
{
	FString txtTaskCount = TEXT("Task Done : ") + FString::FromInt(gameInstance->GetTaskCount());
	if(gameInstance->GetPlayCycle() != nullptr)
	{
		FString txtTimer = TEXT("Time left : ") + gameInstance->GetPlayCycle()->GetTimer();
		textTimer->SetText(FText::FromString(txtTimer));
	}
	textTaskCount->SetText(FText::FromString(txtTaskCount));
}

void UUserWidgetDefaultHUD::UpdatePerks()
{
	if(IsValid(m_player1))
	{
		//First Perk Icon
		UTexture2D* FirstPerkTexture = textureItemEmpty;
		if(IsValid(m_player1->GetFirstPerk()))
		{
			FirstPerkTexture = m_player1->GetFirstPerk()->GetTextureIcon();
		}
		imgPerk1Player1->SetBrushFromTexture(FirstPerkTexture, false);
		//Second Perk Icon
		UTexture2D* SecondPerkTexture = textureItemEmpty;
		if(IsValid(m_player1->GetSecondPerk()))
		{
			SecondPerkTexture = m_player1->GetSecondPerk()->GetTextureIcon();
		}
		imgPerk2Player1->SetBrushFromTexture(SecondPerkTexture, false);
	}

	if(IsValid(m_player2))
	{
		//First Perk Icon
		UTexture2D* FirstPerkTexture = textureItemEmpty;
		if(IsValid(m_player2->GetFirstPerk()))
		{
			FirstPerkTexture = m_player2->GetFirstPerk()->GetTextureIcon();
		}
		imgPerk1Player2->SetBrushFromTexture(FirstPerkTexture, false);
		//Second Perk Icon
		UTexture2D* SecondPerkTexture = textureItemEmpty;
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

void UUserWidgetDefaultHUD::UpdateDisplayText()
{
	//player 1 > player 2
		//item > Element

	if(m_player1)
	{
		if( IsValid(m_player1->GetNearInteractibleItem()))
		{
			UpdateDisplayTextItem(1);
			ShowInteractPlayer1();
		}
		else if ( IsValid(m_player1->GetNearInteractibleElement()))
		{
			UpdateDisplayTextElement(1);
			ShowInteractPlayer1();
		}
		else
		{
			//Hide
			HideInteractPlayer1();
		}
	}

	if(m_player2)
	{
		if( IsValid(m_player2->GetNearInteractibleItem()))
		{
			UpdateDisplayTextItem(2);
			ShowInteractPlayer2();
		}
		else if ( IsValid(m_player2->GetNearInteractibleElement()))
		{
			UpdateDisplayTextElement(2);
			ShowInteractPlayer2();
		}
		else
		{
			//Hide
			HideInteractPlayer2();
		}
	}
	
}

void UUserWidgetDefaultHUD::UpdateDisplayTextItem(int nbPlayerId)
{
	if(nbPlayerId == 1 && m_player1)
	{
		if(IsValid(m_player1->GetNearInteractibleItem()))
		{
			FString txtDisplayElement = "Press E to interact with " + m_player1->GetNearInteractibleItem()->GetItemName();
			SetTextInteractPlayer1(txtDisplayElement);
		}
	}
	
	if(nbPlayerId == 2 && m_player2)
	{
		if(IsValid(m_player2->GetNearInteractibleItem()))
		{
			FString txtDisplayElement = "Press E to interact with " + m_player2->GetNearInteractibleItem()->GetItemName();
			SetTextInteractPlayer2(txtDisplayElement);
		}
	}
}

void UUserWidgetDefaultHUD::UpdateDisplayTextElement(int nbPlayerId)
{
	if(nbPlayerId == 1 && m_player1)
	{
		if(IsValid(m_player1->GetNearInteractibleElement()))
		{
			FString txtDisplayElement  = m_player1->GetNearInteractibleElement()->GetDisplayText();
			SetTextInteractPlayer1(txtDisplayElement);
		}
	}
	
	if(nbPlayerId == 2 && m_player2)
	{
		if(IsValid(m_player2->GetNearInteractibleElement()))
		{
			FString txtDisplayElement = m_player2->GetNearInteractibleElement()->GetDisplayText();
			SetTextInteractPlayer2(txtDisplayElement);
		}
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

void UUserWidgetDefaultHUD::SetProgressBarValue(int nbPlayerId, float fValue)
{
	fValue = fValue / 100.0f; //convert value to percent
	
	if(nbPlayerId == 1 && m_player1)
	{
		if( progressbarPlayer1)
		{
			progressbarPlayer1->SetVisibility(ESlateVisibility::Visible);
			progressbarPlayer1->SetPercent(fValue);
		}
	}
	
	if(nbPlayerId == 2 && m_player2)
	{
		if( progressbarPlayer2)
		{
			progressbarPlayer2->SetVisibility(ESlateVisibility::Visible);
			progressbarPlayer2->SetPercent(fValue);
		}
	}
}

void UUserWidgetDefaultHUD::HideProgressBar(int nbPlayerId)
{
		if(nbPlayerId == 1 && m_player1)
    	{
    		if( progressbarPlayer1)
    		{
    			progressbarPlayer1->SetVisibility(ESlateVisibility::Hidden);
    		}
    	}
    	
    	if(nbPlayerId == 2 && m_player2)
    	{
    		if( progressbarPlayer2)
    		{
    			progressbarPlayer2->SetVisibility(ESlateVisibility::Hidden);
    		}
    	}
}
