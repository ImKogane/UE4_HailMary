#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayCycle.generated.h"

#pragma  region ForwardDeclaration
	class UMainGameInstance;
#pragma endregion 

UCLASS()
class HAILMARY_API APlayCycle : public AActor
{
	GENERATED_BODY()
	
public:
	#pragma region PublicFunctions
		// Sets default values for this actor's properties
		APlayCycle();
		// Called every frame
		virtual void Tick(float DeltaTime) override;
		UFUNCTION()
		FString GetTimer();
		UFUNCTION()
		void ResetTimer();
		UFUNCTION()
		void StopTimer();
	#pragma endregion 

protected:
	#pragma region ProtectedVariables
		UPROPERTY(EditAnywhere, Category = "Gameplay")
		int InitialLoopTime;
		UPROPERTY(EditAnywhere, Category = "Gameplay")
		int LoopTime;
		UPROPERTY(VisibleAnywhere, Category = "Gameplay")
		FTimerHandle GameTimer;
		UPROPERTY()
		UMainGameInstance* TheGameInstance;
	#pragma endregion
	
	#pragma region ProtectedFunctions
		UFUNCTION()
		virtual void BeginPlay() override;
		void Loop();
		UFUNCTION()
		void Clock();
		UFUNCTION()
		void ShowTimer();
	#pragma endregion 
};
