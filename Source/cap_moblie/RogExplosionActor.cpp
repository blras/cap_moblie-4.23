// Fill out your copyright notice in the Description page of Project Settings.


#include "RogExplosionActor.h"
#include "RogCharacter.h"
#include "UserChar.h"
#include "RogMonk.h"
#include "Engine.h"

ARogExplosionActor::ARogExplosionActor()
{
	InitialLifeSpan = 0.6f;
	EffectMovement->InitialSpeed = 0.f;
	EffectMovement->MaxSpeed = 0.f;
}
void ARogExplosionActor::HitActor(AActor* OtherActor)
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
			if (Cast<ARogMonk>(OtherActor))
			{
				ARogMonk* boss = Cast<ARogMonk>(OtherActor);
				boss->SetBreakeRate(boss->GetBreakRate() - 10);
			}
		}

	}
}