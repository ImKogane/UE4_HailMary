// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetPauseMenu.h"

#include "Components/Button.h"
#include "HailMary/Interface/HUD/GameHUD.h"
#include "Kismet/GameplayStatics.h"

void UUserWidgetPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	GameHud = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	
	BtnResume->OnClicked.AddUniqueDynamic(this, &UUserWidgetPauseMenu::ResumeGame);
	BtnSettings->OnClicked.AddUniqueDynamic(this, &UUserWidgetPauseMenu::ShowSettingsMenu);
	BtnMenu->OnClicked.AddUniqueDynamic(this, &UUserWidgetPauseMenu::BackToMenu);

	UE_LOG(LogTemp, Warning, TEXT("INIT"));
	
}

void UUserWidgetPauseMenu::ResumeGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
	GameHud->ShowDefaultHUD(true);
	GameHud->ShowPauseMenu(false);
}

void UUserWidgetPauseMenu::ShowSettingsMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("Open settings"));
}

void UUserWidgetPauseMenu::BackToMenu()
{
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 1);
	UGameplayStatics::RemovePlayer(controller, true);
	UGameplayStatics::OpenLevel(GetWorld(),"MainMenu_Level");
	UE_LOG(LogTemp, Warning, TEXT("Go to menu"));
}
