#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Perk_BaseComponent.generated.h"

UENUM()
enum PerkType
{
	Passive     UMETA(DisplayName = "Passive"),
	Active      UMETA(DisplayName = "Active"),
};

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HAILMARY_API UPerk_BaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	#pragma region PublicFunctions
		// Sets default values for this component's properties
		UPerk_BaseComponent();
		// Called every frame
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		UFUNCTION()
		virtual void UsePerk();
	#pragma endregion 

protected:
	#pragma region ProtectedVariable
		UPROPERTY(EditDefaultsOnly, Category="Perk Description")
		int _nbID;
		UPROPERTY(EditDefaultsOnly, Category="Perk Description")
		FString _strName;
		UPROPERTY(EditDefaultsOnly, Category="Perk Description")
		TEnumAsByte<PerkType> _perkType;
		UPROPERTY(EditDefaultsOnly, Category="Perk Description")
		FString _strEffect;
	#pragma endregion 
	
	#pragma region ProtectedFunctions
		// Called when the game starts
		virtual void BeginPlay() override;
	#pragma endregion 
};
