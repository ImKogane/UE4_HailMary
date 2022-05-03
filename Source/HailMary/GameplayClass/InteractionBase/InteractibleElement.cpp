// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractibleElement.h"

#include "HailMary/MainGameInstance.h"
#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractibleElement::AInteractibleElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Base"));
	BaseComponent->SetupAttachment(RootComponent);

	
	ElementMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ElementMesh"));
	ElementMesh->SetupAttachment(BaseComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision box"));
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetBoxExtent(FVector(20.f, 20.f, 20.f));
	CollisionBox->SetupAttachment(ElementMesh);
	
}

// Called when the game starts or when spawned
void AInteractibleElement::BeginPlay()
{
	Super::BeginPlay();
	//Bind event
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractibleElement::OnBoxOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AInteractibleElement::OnBoxOverlapEnd);
	//Get References
	_gameHud = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	_gameInstance = Cast<UMainGameInstance>(GetGameInstance());
}

// Called every frame
void AInteractibleElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractibleElement::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
								const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("Element near"));
	AStudentCharacter* Player = Cast<AStudentCharacter>(OtherActor);
	if (Player == nullptr)
	{
		//Overlap actor isn't the player
		return;
	}

	Player->SetNearElement(this);
}

void AInteractibleElement::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AStudentCharacter* Player = Cast<AStudentCharacter>(OtherActor);
	if (Player == nullptr)
	{
		//Overlap actor isn't the player
		return;
	}

	Player->SetNearElement(nullptr);
}

void AInteractibleElement::Interaction(AActor* Character)
{
//	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("Element interaction"));
}

