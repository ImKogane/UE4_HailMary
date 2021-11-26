// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractibleItem.h"

#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"

// Sets default values
AInteractibleItem::AInteractibleItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Base"));
	BaseComponent->SetupAttachment(RootComponent);
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(BaseComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision box"));
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetBoxExtent(FVector(20.f, 20.f, 20.f));
	CollisionBox->SetupAttachment(ItemMesh);

	

}

// Called when the game starts or when spawned
void AInteractibleItem::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractibleItem::OnBoxOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AInteractibleItem::OnBoxOverlapEnd);
	
}

// Called every frame
void AInteractibleItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractibleItem::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
								const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Item near"));
	AStudentCharacter* Player = Cast<AStudentCharacter>(OtherActor);
	if (Player == nullptr)
	{
		//Overlap actor isn't the player
		return;
	}

	Player->SetNearItem(this);
}

void AInteractibleItem::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AStudentCharacter* Player = Cast<AStudentCharacter>(OtherActor);
	if (Player == nullptr)
	{
		//Overlap actor isn't the player
		return;
	}

	Player->SetNearItem(nullptr);
}

void AInteractibleItem::Take()
{
	
}

void AInteractibleItem::Use()
{
	
}

