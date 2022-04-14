// Fill out your copyright notice in the Description page of Project Settings.


#include "GluePot.h"

AGluePot::AGluePot()
{

}

void AGluePot::Effect()
{
	Super::Effect();
	this->Destroy();
}
