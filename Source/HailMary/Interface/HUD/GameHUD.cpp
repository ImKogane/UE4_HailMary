// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if( IsValid(_bpWidgetDefaultHUD))
	{
		_widgetDefaultHUD = CreateWidget<UUserWidgetDefaultHUD>(GetWorld(), _bpWidgetDefaultHUD);
		_widgetDefaultHUD->AddToViewport();
		_widgetDefaultHUD->GetReferences();
	}
}

void AGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
		
	if( IsValid(_widgetDefaultHUD))
	{
		_widgetDefaultHUD->UpdateWidget();
	}
}
