// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetPauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API UUserWidgetPauseMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	class AGameHUD* GameHud;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, OptionalWidget=true))
	class UButton* BtnResume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, OptionalWidget=true))
	class UButton* BtnSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, OptionalWidget=true))
	class UButton* BtnMenu;

	UFUNCTION(BlueprintCallable)
	void ResumeGame();

	UFUNCTION(BlueprintCallable)
	void ShowSettingsMenu();

	UFUNCTION(BlueprintCallable)
	void BackToMenu();
	
};
