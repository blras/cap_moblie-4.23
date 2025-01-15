// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "RogExplosionActor.generated.h"

/**
 * 
 */
UCLASS()
class CAP_MOBLIE_API ARogExplosionActor : public ABullet
{
	GENERATED_BODY()
public:
	ARogExplosionActor();
	virtual void HitActor(AActor* OtherActor) override;
};
