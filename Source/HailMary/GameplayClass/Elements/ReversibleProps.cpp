// Fill out your copyright notice in the Description page of Project Settings.


#include "ReversibleProps.h"

#include "HailMary/Characters/StudentCharacter/StudentCharacter.h"

AReversibleProps::AReversibleProps()
{
	CollisionBox->SetupAttachment(BaseComponent);
}

void AReversibleProps::BeginPlay()
{
	Super::BeginPlay();

	if(CurveFloat)
	{
		FOnTimelineFloat TimeLineProgress;
		TimeLineProgress.BindUFunction(this, FName("TimeLineProgress"));

		CurveTimeLine.AddInterpFloat(CurveFloat, TimeLineProgress);
		CurveTimeLine.SetLooping(false);

		StartRot = EndRot = GetActorRotation();
		EndRot.Roll += ZOffset;

		
	}
	
}

void AReversibleProps::Interaction(AActor* Character)
{
	Super::Interaction(Character);

	if(!IsFalling && !IsReverse)
	{
		AStudentCharacter* Player = Cast<AStudentCharacter>(Character);

		if(Player == nullptr) { return; }

		IsFalling = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Falling ..."));
		CurveTimeLine.PlayFromStart();
	}
	
}

void AReversibleProps::FallEffect()
{
	Destroy(true);
}


void AReversibleProps::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CurveTimeLine.TickTimeline(DeltaSeconds);
	
	if(!CurveTimeLine.IsPlaying() && !IsReverse && IsFalling)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("A terre."));
		IsReverse = true;
		IsFalling = false;
		
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(
			UnusedHandle, this, &AReversibleProps::FallEffect, 10.0f, false);
	}
}

void AReversibleProps::TimeLineProgress(float Value)
{
	FRotator NewRot = FMath::Lerp(StartRot, EndRot, Value);
	SetActorRotation(NewRot);
}



