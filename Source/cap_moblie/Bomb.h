// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "Bomb.generated.h"

/**
 * 
 */
UCLASS()
class CAP_MOBLIE_API ABomb : public ABullet
{
	GENERATED_BODY()
public:
	ABomb();
	virtual void HitActor(AActor* OtherActor) override;
};
