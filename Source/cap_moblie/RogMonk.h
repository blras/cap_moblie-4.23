// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "RogMonk.generated.h"

/**
 * 
 */
UCLASS()
class CAP_MOBLIE_API ARogMonk : public AEnemy
{
	GENERATED_BODY()
public:
		ARogMonk();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Landed(const FHitResult& Hit) override;
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* UpperComponent;
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* LowerComponent;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* AShotSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* BShotSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* CShotSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* HotShotSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* ChargeShotSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* ChargeSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* StartSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* EngageSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* JumpStartSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* LandingSound;
	//UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		//class USoundBase* TeleportSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* DamagedSound;

	UAnimMontage* AAnimmontage;
	UAnimMontage* BAnimmontage;
	UAnimMontage* CAnimmontage;
	UAnimMontage* ChargeShotAnimmontage;
	UAnimMontage* ChargeAnimmontage;
	UAnimMontage* JumpAnimmontage;
	UAnimMontage* LandingAnimmontage;
	//UAnimMontage* TeleportAnimmontage;
	UAnimMontage* HotShotAnimmontage;
	UAnimMontage* UpperArm;
	UAnimMontage* LowerArm;

	UParticleSystem* ChargeEffect;
	UParticleSystem* ChargeHitEffect;
	UParticleSystem* JumpEffect;
	//UParticleSystem* TeleportEffect;

	float BreakRate;

private:
	float JumpRate;
	float ChargeRate;
	float TeleportRate;
	float HotShotRate;

	int testi;

	int combonum;

	TArray<int> phase;

public:
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class ARogEffect* ChargeBullet;

	UFUNCTION(BlueprintNativeEvent, Category = Any)
	void BossAI();
	void Jump();
	void Charge();
	void Teleport();
	void HotShot(FVector FireDirection);
	void ChargeShot();
	void JumpBall();
	void Combo(FVector FireDirection);
	float GetBreakRate();
	void SetBreakeRate(float brate);
};
