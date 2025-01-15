// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogCharacter.h"
#include "Enemy.generated.h"

UCLASS()
class CAP_MOBLIE_API AEnemy : public ARogCharacter
{
	GENERATED_BODY()
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class AUserChar *User;
public:
	// Sets default values for this pawn's properties
	AEnemy();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UAnimMontage* TeleportAnimmontage;

	UParticleSystem* TeleportEffect;

	FTimerHandle TimerHandle_TeleportTimerExpired;
	FTimerHandle TimerHandle_HealTimerExpired;
	FTimerHandle TimerHandle_CResurrectTimerExpired;

	bool forboss;
	bool HasHpRegen;
	bool HasTel;
	bool bCanTel;
	bool HasHeal;
	bool bCanHeal;
	bool HasCastResurrect;
	bool bCastResurrect;
	int EnemyNum;
	void HpRegeneration();
	void Teleport();
	void TeleportCool();
	void Heal();
	void HealCool();
	void CastResurrect();
	void CastResurrectCool();
	void SetStat();

private:
	void SetEnemy();
public:	
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	FVector GoalLoation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	class USphereComponent* PunchSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	class UBoxComponent* HitBox;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* TeleportSound;

	UFUNCTION(BlueprintNativeEvent, Category = Any)
	void Sight();
	UFUNCTION(BlueprintNativeEvent, Category = Any)
	void Hearing();
	UFUNCTION(BlueprintNativeEvent, Category = Any)
	void Move();
	// Called every frame
	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void OnAttack(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintNativeEvent, Category = Any)
	void OnTarget(AActor* Actors);

	void SetEnemyNum(int n);
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
