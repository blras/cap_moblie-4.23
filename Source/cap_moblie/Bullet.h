// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogEffect.h"
#include "Bullet.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
UCLASS(config = Game)
class CAP_MOBLIE_API ABullet : public ARogEffect
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	//Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BulletMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* HitComponent;

	class UParticleSystem* HitParticle;

	int32 Dmg;
public:	
	// Called every frame
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnOverlap(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(Category = Mesh, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	 class ARogCharacter* Shooter;


	virtual void HitActor(AActor* OtherActor);
	void SetHitParticle(UParticleSystem* particle);
	void SetDmg(int32 dmg);
	FORCEINLINE UStaticMeshComponent* GetBulletMesh() const { return BulletMeshComponent; }
	/** Returns ProjectileMovement subobject **/
};
