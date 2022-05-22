// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetWinScreen.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API UUserWidgetWinScreen : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnPlayAgain;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnMenu;
	
	UFUNCTION(BlueprintCallable)
	void PlayAgain();

	UFUNCTION(BlueprintCallable)
	void BackToMenu();
	
};
