// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetWinScreen.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UUserWidgetWinScreen::NativeConstruct()
{
	Super::NativeConstruct();
	
	
	BtnPlayAgain->OnClicked.AddUniqueDynamic(this, &UUserWidgetWinScreen::PlayAgain);
	BtnMenu->OnClicked.AddUniqueDynamic(this, &UUserWidgetWinScreen::BackToMenu);

	UE_LOG(LogTemp, Warning, TEXT("INIT"));
}

void UUserWidgetWinScreen::PlayAgain()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Proto_Level_02");
}

void UUserWidgetWinScreen::BackToMenu()
{
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 1);
	UGameplayStatics::RemovePlayer(controller, true);
	
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu_Level");
}