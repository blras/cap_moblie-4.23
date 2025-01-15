// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Gun.generated.h"

/**
 * 
 */
UCLASS()
class CAP_MOBLIE_API AGun : public AItem
{
	GENERATED_BODY()
public:
	AGun();
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	FVector GunOffset;
};
