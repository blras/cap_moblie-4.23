              // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogCharacter.h"
#include "UserChar.generated.h"

UCLASS()
class CAP_MOBLIE_API AUserChar : public ARogCharacter
{
	GENERATED_BODY()

	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
public:
	// Sets default values for this character's properties
	AUserChar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		class UAnimBlueprint* dyn_animbps;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	//UFUNCTION(BlueprintNativeEvent, Category = Any)
		//void Aim();
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FRotator TRDebug;

	UPROPERTY(Category = Mesh, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AEnemy* TargetLock;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class ARogEffect* ChargeBullet;

	void Aim();
	void SetUIHp();
	
	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual void SetLevelCount(int lc) override;
	// End Actor Interface

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName LookForwardBinding;
	static const FName TurnRightBinding;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* GWeaponComponent;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* FlameSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* ChargeSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* ChargeShotSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* ShotGunSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* SpreeSound;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* OasisBgm;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* FairyBgm;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* DampBgm;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* TensionBgm;

	void Combo(FVector FireDirection);
	void ComboReset();
	void ExtraShot(FVector FireDirection, FVector gunoffset);
	void ChannelShot(FVector FireDirection);
	void SwapWeapons(USkeletalMeshComponent* weapon, USkeletalMeshComponent* toweapon);
	void ReStart();
	UAnimMontage* AnimmontageLeft;
	UAnimMontage* AnimmontageRight;
	UAnimMontage* AnimmontageDouble;
	UAnimMontage* AnimmontageShotgun;
	UAnimMontage* AnimmontageCharge;
	UAnimMontage* AnimmontageChargeShot;
	UAnimMontage* AnimmontageChannelStart;
	UAnimMontage* AnimmontageChannel;
	UAnimMontage* AnimmontageChannelEnd;
	FTimerHandle TimerHandle_ComboTimerExpired;
	FTimerHandle TimerHandle_SpreeTimerExpired;
	FTimerHandle TimerHandle_ShotgunTimerExpired;
	FTimerHandle TimerHandle_ChargingTimerExpired;
	FTimerHandle TimerHandle_ChargeTimerExpired;
	FTimerHandle TimerHandle_ChannelTimerExpired;
	FTimerHandle TimerHandle_ChannelingTimerExpired;
	FTimerHandle TimerHandle_SpreeDurationTimerExpired;
	FTimerHandle TimerHandle_ReloadExpired;

	FTimerHandle TimerHandle_SpreeCoolExpired;
	FTimerHandle TimerHandle_ShotgunCoolExpired;
	FTimerHandle TimerHandle_ChargeCoolExpired;
	FTimerHandle TimerHandle_ChannelCoolExpired;
	FTimerHandle TimerHandle_ReloadRateExpired;

	FTimerHandle TimerHandle_ReStartExpired;

	UParticleSystem* ChargeEffect;
	UParticleSystem* ChargeHitEffect;
	UParticleSystem* ChannelEffect;
	UParticleSystem* ChannelHitEffect;

	bool skillsView;
	bool bossinfo;
	float SkillcoolAmount;
	float Spreecool;
	float Shotguncool;
	float Chargecool;
	float Channelcool;
	float Reloadtime;
	float spreePer;
	float shotgunPer;
	float chargePer;
	float channelPer;
	float Spreeduration;
	float AttackRateAmount;
	float reloadPer;
	bool bCanSpree;
	bool Spreeing;
	bool bCanShotgun;
	bool bCanCharge;
	bool bCanChannel;
	bool channeling;
	bool charging;
	bool isReloading;
	bool trigged;
	int skillPoint;
	int Ammo;
	int MaxAmmo;
	TArray<int> SkillLeveli;

private:
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* LeftWeaponComponent;
	
	int combonum;
	int Amo;

public:	


	bool GetitemView();
	void SetitemView(bool itemview);
	void LevelUp();
	void TriggerPressed();
	void TriggerReleased();
	void Reload();
	void Reloading();
	void ReloadCancel();
	void Spree();
	void Shotgun();
	void ShotgunCool();
	void SpreeCool();
	void SpreeDuration();
	void Charge();
	void ChargeShot();
	void ChargeCool();
	void Channeling();
	void ChannelingOff();
	void ChannelingCool();
	void SpreePer();
	void ShotgunPer();
	void ChannelPer();
	void ChargePer();
	void ReloadPer();
	void SetSkillPoint(int point);
	int GetSkillPoint();
	float GetSkillCooldown(int skill);
	void SkillLevelUp(int Skillnum);
	int GetSkillLevel(int Skillnum);
	void BCanSkill(int Skillnum);
	int GetAmmo();
	int GetMaxAmmo();
	float GetReloadRate();
	//void GetExp(int exp)
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent, Category = "Skills")
	void ChannelingStart();

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* StageBgm;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* BossBgm;

	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void Prox(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/** Returns ShipMeshComponent subobject **/
	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	// Called every frame
//	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
