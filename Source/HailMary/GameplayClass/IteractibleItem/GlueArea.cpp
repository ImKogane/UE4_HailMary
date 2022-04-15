// Fill out your copyright notice in the Description page of Project Settings.


#include "HailMary/GameplayClass/IteractibleItem/GlueArea.h"
#include "HailMary/Characters/IA_Boss/AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AGlueArea::AGlueArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Base"));
	BaseComponent->SetupAttachment(RootComponent);

	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	DecalComponent->SetupAttachment(BaseComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision box"));
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetBoxExtent(FVector(20.f, 20.f, 20.f));
	CollisionBox->SetupAttachment(DecalComponent);
}

// Called when the game starts or when spawned
void AGlueArea::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGlueArea::OnBoxOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AGlueArea::OnBoxOverlapEnd);
	
}

// Called every frame
void AGlueArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGlueArea::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
								const FHitResult& SweepResult)
{
	AAICharacter* AI = Cast<AAICharacter>(OtherActor);
	if (AI != nullptr)
	{
		AI->GetCharacterMovement()->MaxWalkSpeed /= reduceRate;
	}
}

void AGlueArea::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AAICharacter* AI = Cast<AAICharacter>(OtherActor);
	if (AI != nullptr)
	{
		AI->GetCharacterMovement()->MaxWalkSpeed *= reduceRate;
	}
}

