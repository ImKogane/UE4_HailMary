// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

#include "Kismet/GameplayStatics.h"


void AGameHUD::BeginPlay()
{
	Super::BeginPlay();
	
	//Singleton
	AActor* inst = UGameplayStatics::GetActorOfClass(GetWorld(),AGameHUD::StaticClass());
	if( IsValid(inst) && inst!= this)
	{
		this->Destroy();
	}
	else
	{
		if( IsValid(_bpWidgetDefaultHUD))
		{
			_widgetDefaultHUD = CreateWidget<UUserWidgetDefaultHUD>(GetWorld(), _bpWidgetDefaultHUD);
			_widgetDefaultHUD->AddToViewport();
			_widgetDefaultHUD->GetReferences();
		}
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
