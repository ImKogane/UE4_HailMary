// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HailMary/Interface/UserWidgets/UserWidgetMainMenu.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	FORCEINLINE UUserWidgetMainMenu* GetMainMenuWidget(){return WidgetMainMenu;}
	UFUNCTION()
	void Init();

	UFUNCTION() void ShowMainMenu(bool state);
	
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidgetMainMenu> BPWidgetMainMenu;
	UPROPERTY()
	UUserWidgetMainMenu* WidgetMainMenu;
	
};
