// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

#include "Kismet/GameplayStatics.h"


void AGameHUD::Init()
{
	if( IsValid(BPWidgetDefaultHUD))
	{
		WidgetDefaultHUD = CreateWidget<UUserWidgetDefaultHUD>(GetWorld(), BPWidgetDefaultHUD);
		WidgetDefaultHUD->AddToViewport();
		WidgetDefaultHUD->GetReferences();
	}

	if( IsValid(BPWidgetPauseMenu))
	{
		WidgetPauseMenu = CreateWidget<UUserWidgetPauseMenu>(GetWorld(), BPWidgetPauseMenu);
		WidgetPauseMenu->AddToViewport();
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
