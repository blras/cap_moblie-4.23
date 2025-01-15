// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "RogCharacter.h"
#include "UserChar.h"
#include "RogMonk.h"
#include "RogExplosionActor.h"
#include "Engine.h"

ABomb::ABomb()
{

}
void ABomb::HitActor(AActor* OtherActor)
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
			if (World != NULL)
			{
				ARogExplosionActor* explsionActor;
				// spawn the projectile
				explsionActor = World->SpawnActor<ARogExplosionActor>(GetActorLocation(), GetActorRotation());
				explsionActor->Shooter = this->Shooter;
				explsionActor->SetDmg(Dmg);
				if (HitParticle != nullptr)
				{
					explsionActor->SetParticle(HitParticle);
					explsionActor->SetHitParticle(HitParticle);
				}
				/*if (AttackSound != nullptr)
				{
					UGameplayStatics::PlaySoundAtLocation(this, AttackSound, GetActorLocation());
				}*/
			}
		}
		Destroy();


	}
}