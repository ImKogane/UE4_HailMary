// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"

#include "Kismet/GameplayStatics.h"

void AMainMenuHUD::Init()
{
	if( IsValid(BPWidgetMainMenu))
	{
		WidgetMainMenu = CreateWidget<UUserWidgetMainMenu>(GetWorld(), BPWidgetMainMenu);
		WidgetMainMenu->AddToViewport();
		WidgetMainMenu->SetVisibility(ESlateVisibility::Visible);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	}
	
}

void AMainMenuHUD::ShowMainMenu(bool state)
{
	if(state)
	{
		WidgetMainMenu->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		WidgetMainMenu->SetVisibility(ESlateVisibility::Hidden);
	}
}