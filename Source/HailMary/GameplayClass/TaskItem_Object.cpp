// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskItem_Object.h"


ATaskItem_Object::ATaskItem_Object()
{
	BaseComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Base"));
	BaseComponent->SetupAttachment(RootComponent);
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(BaseComponent);
}
