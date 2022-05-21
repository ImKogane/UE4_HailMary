// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetLoseScreen.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API UUserWidgetLoseScreen : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnRetry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnMenu;
	
	UFUNCTION(BlueprintCallable)
	void Retry();

	UFUNCTION(BlueprintCallable)
	void BackToMenu();
};
