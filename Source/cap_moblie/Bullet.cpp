// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/CollisionProfile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "RogCharacter.h"
#include "UserChar.h"
#include "RogMonk.h"
#include "Engine.h"
// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitComponent"));
	HitComponent->RelativeRotation = FRotator(90,0,0);
	HitComponent->SetCapsuleHalfHeight(62.0);
	HitComponent->SetCapsuleRadius(7.0);
	HitComponent->SetupAttachment(RootComponent);
	HitComponent->SetEnableGravity(true);
	HitComponent->BodyInstance.SetCollisionProfileName("OverlapAll");
	HitComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);

	EffectMovement->InitialSpeed = 3072.f;
	EffectMovement->MaxSpeed = 3072.f;
	EffectMovement->bRotationFollowsVelocity = true;
	EffectMovement->bShouldBounce = false;
	EffectMovement->ProjectileGravityScale = 0.f; // No gravity

	// Die after 3 seconds by default
	InitialLifeSpan = 2.0f;
	Dmg = 5;
}

// Called when the game starts or when spawned

// Called every frame
void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<ARogCharacter>(OtherActor) == nullptr)
	{
		return;
	}
	//FString debug = "onhit";
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, debug);
	//Destroy();
}
void ABullet::OnOverlap(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HitActor(OtherActor);
}
void ABullet::SetHitParticle(UParticleSystem* particle)
{
	HitParticle = particle;
}
void ABullet::SetDmg(int32 dmg)
{
	Dmg = dmg;
}
void ABullet::HitActor(AActor* OtherActor)
{
	UWorld* const World = GetWorld();
	if (World != NULL)
	{

	}
	if (ParticleComponent != nullptr && HitParticle != nullptr)
	{
		if (Cast<ARogCharacter>(OtherActor) == nullptr || Cast<ARogCharacter>(OtherActor) == Shooter)
		{
			return;
		}
		else
		{
			ARogCharacter* target = Cast<ARogCharacter>(OtherActor);
			target->HitDamage(Dmg, GetActorForwardVector());
			if (Cast<AUserChar>(OtherActor))
			{
				AUserChar* user = Cast<AUserChar>(OtherActor);
				user->SetUIHp();
			}
			else
			{
				if (target->Target == nullptr && Shooter !=nullptr)
					target->Target = Shooter;
			}
			if (Cast<ARogMonk>(OtherActor))
			{
				ARogMonk* boss = Cast<ARogMonk>(OtherActor);
				boss->SetBreakeRate(boss->GetBreakRate() - 10);
			}
		}
		UGameplayStatics::SpawnEmitterAtLocation(World, HitParticle, GetActorLocation(), GetActorRotation());
		Destroy();
	}
}