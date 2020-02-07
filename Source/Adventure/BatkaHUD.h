// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BatkaHUD.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTURE_API ABatkaHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;
public:
	// Primary draw call for the HUD.
	virtual void DrawHUD() override;
};
