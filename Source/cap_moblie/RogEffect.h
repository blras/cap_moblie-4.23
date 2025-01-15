// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogEffect.generated.h"

/**
 * 
 */
class UProjectileMovementComponent;
class UStaticMeshComponent;
UCLASS(config = Game)
class CAP_MOBLIE_API ARogEffect : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ARogEffect();
protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* ParticleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* EffectMovement;
public:
	void EndEffect();
	void SetParticle(UParticleSystem* particle);


	FORCEINLINE UProjectileMovementComponent* GetEffectMovement() const { return EffectMovement; }
};
