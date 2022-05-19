// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetMainMenu.h"

#include "Components/Button.h"
#include "HailMary/Interface/HUD/MainMenuHUD.h"
#include "Kismet/GameplayStatics.h"

void UUserWidgetMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	HUDMainMenu = Cast<AMainMenuHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	
	BtnPlay->OnClicked.AddUniqueDynamic(this, &UUserWidgetMainMenu::PlayGame);
	BtnSettings->OnClicked.AddUniqueDynamic(this, &UUserWidgetMainMenu::ShowSettingsMenu);
	BtnExit->OnClicked.AddUniqueDynamic(this, &UUserWidgetMainMenu::ExitGame);

	UE_LOG(LogTemp, Warning, TEXT("INIT"));
}

void UUserWidgetMainMenu::PlayGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Proto_Level_02");
}

void UUserWidgetMainMenu::ShowSettingsMenu()
{
}

void UUserWidgetMainMenu::ExitGame()
{
    GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
