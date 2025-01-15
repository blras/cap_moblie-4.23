// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RogCharacter.generated.h"

UCLASS()
class CAP_MOBLIE_API ARogCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ARogCharacter();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* MeshComponent;
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* WeaponComponent;	
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* AimComponent;
	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* HpWidgetComp;
	UPROPERTY(VisibleAnywhere)
		class URogHpbar* HpbarRef;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* AttackSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* HitSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* DeathSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* ResurrectSound;

	virtual void BeginPlay() override;

	uint32 bCanFire : 1;
	uint32 bCanDmg : 1;
	int32 Dmg;
	FTimerHandle TimerHandle_ShotTimerExpired;
	FTimerHandle TimerHandle_HpTimerExpired;
	FTimerHandle TimerHandle_DeathTimerExpired;
	UAnimMontage* Animmontage;
	UAnimMontage* Deathmontage;
	UAnimMontage* snapAnimmontage;
	UAnimMontage* GunAnimmontage;
	UAnimMontage* HealAnimmontage;
	UAnimMontage* ResurrectAnimmontage;
	UParticleSystem* BulletEffect;
	UParticleSystem* HitEffect;
	UParticleSystem* ResurrectEffect;
	FString Name;
	bool live;
	bool isboss;
	bool bCanResurrect;
	float CooldownRate;
	double Crit;
	double CritDmg;
	int Armor;
	bool isSkillCast;
	int levelcount;

	void Resurrect();


public:	
	FString faction;
	int32 range;
	int64 Uidmg;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetLevelCount(int lc);

	UPROPERTY(Category = Mesh, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ARogCharacter* Target;
	UPROPERTY(Category = Mesh, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ARogCharacter* FTarget;
	UPROPERTY(Category = Mesh, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ARogCharacter* CTarget;
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class AItem* EItem;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float AttackRate;
	/*UFUNCTION(BlueprintNativeEvent, Category = Any)
	void HitDamage(int damage, FVector dir);*/
	/* The speed our ship moves around the level */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float Hp;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	int MaxHp;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	int Exp;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	int Level;
	/** Sound to play each time we fire */

	UFUNCTION(BlueprintNativeEvent, Category = Any)
	void HitDamage(int damage, FVector dir);
	/* Fire a shot in the specified direction */
	void Attack(FVector FireDirection,FVector gunoffset);
	/* Handler for the fire timer expiry */
	void AttackTimerExpired();
	void HpBarTimerExpired();
	float GetHp();
	float GetMaxHp();
	int GetExp();
	void SetExp(int exp);
	int GetNextExp();
	void Death();
	void SetResurrect(bool r);
	bool GetResurrect();
	UFUNCTION(BlueprintNativeEvent, Category = Any)
	void Equip(AItem* item);
	bool isBoss();
	bool isLive();
	void SetDmg(int32 dmg);
	void SetMaxHp(int32 maxhp);
	void SetMoveSpeed(float movespeed);
	void SetCooldownRate(float cooldownrate);
	void ObjDestroy();
	void DropItem();
	int GetLevelCount();
	FString GetName();
	// Called to bind functionality to input
	FORCEINLINE class USkeletalMeshComponent* GetMeshComponent() const { return MeshComponent; }
	FORCEINLINE class USkeletalMeshComponent* GetWeaponComponent() const { return WeaponComponent; }
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
