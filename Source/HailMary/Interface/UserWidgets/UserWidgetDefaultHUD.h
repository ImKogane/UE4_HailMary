// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"
#include "UserWidgetDefaultHUD.generated.h"

#pragma region ForwardDeclaration
	class UMainGameInstance;
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
		#pragma endregion

		#pragma region MiddleBlock
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UTextBlock* textTimer;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UTextBlock* textTaskCount;
		#pragma endregion

		#pragma region Player1
			UPROPERTY()
			AStudentCharacter* m_player1;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UTextBlock* textItemPlayer1;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UImage* imgItemPlayer1;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UImage* imgPerk1Player1;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UImage* imgPerk2Player1;
		#pragma endregion
	
		#pragma region Player2
			UPROPERTY()
			AStudentCharacter* m_player2;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UTextBlock* textItemPlayer2;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UImage* imgItemPlayer2;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UImage* imgPerk1Player2;
			UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
			class UImage* imgPerk2Player2;
		#pragma endregion 

		#pragma region PublicFunctions
			UFUNCTION()
			void GetReferences();
			UFUNCTION()
			void UpdateWidget();
			UFUNCTION()
			void UpdatePerks();
			UFUNCTION()
			void UpdateItems();
		#pragma endregion 
};
