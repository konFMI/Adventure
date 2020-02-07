// Fill out your copyright notice in the Description page of Project Settings.


#include "BatkaGameMode.h"
#include <Runtime\Engine\Classes\Engine\Engine.h>

void ABatkaGameMode::StartPlay()
{
	Super::StartPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("We are using the BatkaGameMode"));
	}
}
