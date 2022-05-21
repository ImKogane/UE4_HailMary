// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetLoseScreen.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UUserWidgetLoseScreen::NativeConstruct()
{
	Super::NativeConstruct();
	
	
	BtnRetry->OnClicked.AddUniqueDynamic(this, &UUserWidgetLoseScreen::Retry);
	BtnMenu->OnClicked.AddUniqueDynamic(this, &UUserWidgetLoseScreen::BackToMenu);

	UE_LOG(LogTemp, Warning, TEXT("INIT"));
}

void UUserWidgetLoseScreen::Retry()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Proto_Level_02");
}

void UUserWidgetLoseScreen::BackToMenu()
{
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 1);
	UGameplayStatics::RemovePlayer(controller, true);
	
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu_Level");
}

