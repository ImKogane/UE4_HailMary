// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HailMary/Interface/UserWidgets/UserWidgetDefaultHUD.h"
#include "HailMary/Interface/UserWidgets/UserWidgetLoseScreen.h"
#include "HailMary/Interface/UserWidgets/UserWidgetPauseMenu.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	FORCEINLINE UUserWidgetDefaultHUD* GetDefaultWidget(){return WidgetDefaultHUD;}
	FORCEINLINE UUserWidgetPauseMenu* GetPauseWidget(){return WidgetPauseMenu;}
	FORCEINLINE UUserWidgetLoseScreen* GetLoseWidget(){return WidgetLoseScreen;}
	UFUNCTION()
	void Init();

	UFUNCTION() void ShowPauseMenu(bool state);
	UFUNCTION() void ShowDefaultHUD(bool state);
	UFUNCTION() void ShowLoseScreen(bool state);
	
	protected:
		UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidgetDefaultHUD> BPWidgetDefaultHUD;
		UPROPERTY()
		UUserWidgetDefaultHUD* WidgetDefaultHUD;

		//Pause menu widget
		UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidgetPauseMenu> BPWidgetPauseMenu;
		UPROPERTY()
		UUserWidgetPauseMenu* WidgetPauseMenu;

		//Lose screen widget
		UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidgetLoseScreen> BPWidgetLoseScreen;
		UPROPERTY()
		UUserWidgetLoseScreen* WidgetLoseScreen;

	

		UFUNCTION()
		void BeginPlay() override;
		UFUNCTION()
		void Tick(float DeltaSeconds) override;
};
