// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetDefaultHUD.generated.h"

#pragma region ForwardDeclaration
	class UMainGameInstance;
#pragma endregion 

/**
 * 
 */
UCLASS()
class HAILMARY_API UUserWidgetDefaultHUD : public UUserWidget
{
	GENERATED_BODY()

	public:
		#pragma region PublicVariables
			UPROPERTY()
			UMainGameInstance* gameInstance;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UTextBlock* textTimer;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UTextBlock* textTaskCount;
		#pragma endregion 

		#pragma region PublicFunctions
			UFUNCTION()
			void GetReferences();
			UFUNCTION()
			void UpdateWidget();
		#pragma endregion 
};
