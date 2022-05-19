// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API UUserWidgetMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	class AMainMenuHUD* HUDMainMenu;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnExit;

	UFUNCTION(BlueprintCallable)
	void PlayGame();

	UFUNCTION(BlueprintCallable)
	void ShowSettingsMenu();

	UFUNCTION(BlueprintCallable)
	void ExitGame();
	
};
