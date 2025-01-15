// Fill out your copyright notice in the Description page of Project Settings.


#include "RogEffect.h"
#include "Bullet.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/CollisionProfile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "RogCharacter.h"
#include "UserChar.h"
#include "Engine.h"
ARogEffect::ARogEffect()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PraticleSytem"));
	ParticleComponent->SetupAttachment(RootComponent);

	// set up a notification for when this component hits something
	RootComponent = ParticleComponent;


	EffectMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	EffectMovement->UpdatedComponent = ParticleComponent;
	EffectMovement->InitialSpeed = 0.f;
	EffectMovement->MaxSpeed = 3072.f;
	EffectMovement->bRotationFollowsVelocity = true;
	EffectMovement->bShouldBounce = false;
	EffectMovement->ProjectileGravityScale = 0.f; // No gravity

	// Die after 3 seconds by default
	InitialLifeSpan = 5.f;
}
void ARogEffect::EndEffect()
{
	Destroy();
}
void ARogEffect::SetParticle(UParticleSystem* particle)
{
	ParticleComponent->SetTemplate(particle);
}