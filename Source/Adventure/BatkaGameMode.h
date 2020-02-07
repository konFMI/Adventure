// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BatkaGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTURE_API ABatkaGameMode : public AGameModeBase
{
	GENERATED_BODY()

		virtual void StartPlay() override;
	
};
