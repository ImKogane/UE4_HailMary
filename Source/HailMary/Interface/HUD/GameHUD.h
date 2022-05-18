// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HailMary/Interface/UserWidgets/UserWidgetDefaultHUD.h"
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
		UFUNCTION()
		void Init();
	
	protected:
		UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidgetDefaultHUD> BPWidgetDefaultHUD;
		UPROPERTY()
		UUserWidgetDefaultHUD* WidgetDefaultHUD;

		UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidgetPauseMenu> BPWidgetPauseMenu;
		UPROPERTY()
		UUserWidgetPauseMenu* WidgetPauseMenu;

		UFUNCTION()
		void BeginPlay() override;
		UFUNCTION()
		void Tick(float DeltaSeconds) override;
};
