// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

#include "Kismet/GameplayStatics.h"


void AGameHUD::Init()
{
	if( IsValid(BPWidgetDefaultHUD))
	{
		WidgetDefaultHUD = CreateWidget<UUserWidgetDefaultHUD>(GetWorld(), BPWidgetDefaultHUD);
		WidgetDefaultHUD->AddToViewport();
		WidgetDefaultHUD->SetVisibility(ESlateVisibility::Visible);
		WidgetDefaultHUD->GetReferences();
	}

	if( IsValid(BPWidgetPauseMenu))
	{
		WidgetPauseMenu = CreateWidget<UUserWidgetPauseMenu>(GetWorld(), BPWidgetPauseMenu);
		WidgetPauseMenu->AddToViewport();
		WidgetPauseMenu->SetVisibility(ESlateVisibility::Hidden);
	}

	if( IsValid(BPWidgetLoseScreen))
	{
		WidgetLoseScreen = CreateWidget<UUserWidgetLoseScreen>(GetWorld(), BPWidgetLoseScreen);
		WidgetLoseScreen->AddToViewport();
		WidgetLoseScreen->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AGameHUD::ShowPauseMenu(bool state)
{
	if(state)
	{
		WidgetPauseMenu->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		WidgetPauseMenu->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AGameHUD::ShowDefaultHUD(bool state)
{
	if(state)
	{
		WidgetDefaultHUD->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		WidgetDefaultHUD->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AGameHUD::ShowLoseScreen(bool state)
{
	if(state)
	{
		WidgetLoseScreen->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		WidgetLoseScreen->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	//Singleton
	AActor* inst = UGameplayStatics::GetActorOfClass(GetWorld(),AGameHUD::StaticClass());
	if( IsValid(inst) && inst!= this)
	{
		this->Destroy();
	}
}

void AGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
		
	if( IsValid(WidgetDefaultHUD))
	{
		WidgetDefaultHUD->UpdateWidget();
	}
}
