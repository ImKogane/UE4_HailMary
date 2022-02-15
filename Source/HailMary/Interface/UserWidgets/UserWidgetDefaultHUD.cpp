// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetDefaultHUD.h"

#include "Components/TextBlock.h"
#include "HailMary/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UUserWidgetDefaultHUD::GetReferences()
{
	gameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void UUserWidgetDefaultHUD::UpdateWidget()
{
	if(gameInstance->GetPlayCycle() != nullptr)
	{
		FString txtTimer = TEXT("Time left : ") + gameInstance->GetPlayCycle()->GetTimer();
		textTimer->SetText(FText::FromString(txtTimer));
	}
	
	FString txtTaskCount = TEXT("Taches réaliser : ") + FString::FromInt(gameInstance->GetTaskCount());
	textTaskCount->SetText(FText::FromString(txtTaskCount));
}
