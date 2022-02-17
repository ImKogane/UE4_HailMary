// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetInteractDisplay.generated.h"

/**
 * 
 */
UCLASS()
class HAILMARY_API UUserWidgetInteractDisplay : public UUserWidget
{
	GENERATED_BODY()

	public:
	
		UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
		class UTextBlock* textInteract;
};
