// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "UserWidgetInteractDisplay.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
// #include "HailMary/Characters/StudentCharacter/StudentCharacter.h"
#include "UserWidgetDefaultHUD.generated.h"

#pragma region ForwardDeclaration
	class UMainGameInstance;
	class AStudentCharacter;
#pragma endregion 


UCLASS()
class HAILMARY_API UUserWidgetDefaultHUD : public UUserWidget
{
	GENERATED_BODY()

	public:
		#pragma region RuntimeVariables
			UPROPERTY()
			UMainGameInstance* gameInstance;
			UPROPERTY()
			UTexture2D* textureItemEmpty;
			UPROPERTY()
			bool bPostStartDone = false;
		#pragma endregion

		#pragma region MiddleBlock
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UTextBlock* textTimer;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UTextBlock* textTaskCount;
		#pragma endregion

		#pragma region Player1
			UPROPERTY()
			AStudentCharacter* m_player1 = nullptr;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UTextBlock* textItemPlayer1;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UImage* imgItemPlayer1;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UImage* imgPerk1Player1;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UImage* imgPerk2Player1;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			UUserWidgetInteractDisplay* widgetInteractPlayer1;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			UProgressBar* progressbarPlayer1;
		#pragma endregion
	
		#pragma region Player2
			UPROPERTY()
			AStudentCharacter* m_player2 = nullptr;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UTextBlock* textItemPlayer2;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UImage* imgItemPlayer2;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UImage* imgPerk1Player2;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UImage* imgPerk2Player2;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			UUserWidgetInteractDisplay* widgetInteractPlayer2;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			UProgressBar* progressbarPlayer2;
		#pragma endregion 

		#pragma region PublicFunctions
			UFUNCTION()
			void PostStart();
			UFUNCTION()
			void CheckPostStart();
			UFUNCTION()
			void GetReferences();
			UFUNCTION()
			void UpdateWidget();
			UFUNCTION()
			void UpdateTimer();
			UFUNCTION()
			void UpdateTasks();
			UFUNCTION()
			void UpdatePerks();
			UFUNCTION()
			void UpdateItems();
			UFUNCTION()
			void UpdateDisplayText();
			UFUNCTION()
			void UpdateDisplayTextItem(int nbPlayerId);
			UFUNCTION()
			void UpdateDisplayTextElement(int nbPlayerId);
			UFUNCTION()
			void ShowInteractPlayer1();
			UFUNCTION()
			void ShowInteractPlayer2();
			UFUNCTION()
    		void HideInteractPlayer1();
    		UFUNCTION()
    		void HideInteractPlayer2();
			UFUNCTION()
			void SetTextInteractPlayer1(FString newText);
			UFUNCTION()
			void SetTextInteractPlayer2(FString newText);
			UFUNCTION()
			void SetProgressBarValue(int nbPlayerId, float fValue);
			UFUNCTION()
			void HideProgressBar(int nbPlayerId);
		#pragma endregion 
};
