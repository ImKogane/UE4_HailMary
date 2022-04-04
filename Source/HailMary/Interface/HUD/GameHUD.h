// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HailMary/Interface/UserWidgets/UserWidgetDefaultHUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API AGameHUD : public AHUD
{
	GENERATED_BODY()

	public:
		FORCEINLINE UUserWidgetDefaultHUD* GetDefaultWidget(){return _widgetDefaultHUD;}
		UFUNCTION()
		void Init();
	
	protected:
		UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidgetDefaultHUD> _bpWidgetDefaultHUD;
		UPROPERTY()
		UUserWidgetDefaultHUD* _widgetDefaultHUD;

		UFUNCTION()
		void BeginPlay() override;
		UFUNCTION()
		void Tick(float DeltaSeconds) override;
};
