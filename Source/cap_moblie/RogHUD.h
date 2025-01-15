// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogUserWidget.h"
#include "RogHUD.generated.h"

/**
 * 
 */
UCLASS()
class CAP_MOBLIE_API URogHUD : public URogUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthRed;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBoss;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* BossName;
	UPROPERTY(meta = (BindWidget))
		class UImage* Break0E;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Break0Rate;
	UPROPERTY(meta = (BindWidget))
		class UImage* Break1E;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Break1Rate;
	UPROPERTY(meta = (BindWidget))
		class UImage* Break2E;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Break2Rate;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Ammo;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* Reload;
	UPROPERTY(meta = (BindWidget))
		class UButton* PowerUpLeft;
	UPROPERTY(meta = (BindWidget))
		class UButton* PowerUpCenter;
	UPROPERTY(meta = (BindWidget))
		class UButton* PowerUpRight;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* Experience;

	UPROPERTY(meta = (BindWidget))
		class UButton* SkillsViewBtn;

	UPROPERTY(meta = (BindWidget))
		class UButton* Spree;
	UPROPERTY(meta = (BindWidget))
		class UButton* Shotgun;
	UPROPERTY(meta = (BindWidget))
		class UButton* Channel;
	UPROPERTY(meta = (BindWidget))
		class UButton* Charge;

	UPROPERTY(meta = (BindWidget))
		class UButton* SpreeUp;
	UPROPERTY(meta = (BindWidget))
		class UButton* ShotgunUp;
	UPROPERTY(meta = (BindWidget))
		class UButton* ChannelUp;
	UPROPERTY(meta = (BindWidget))
		class UButton* ChargeUp;
	UPROPERTY(meta = (BindWidget))
		class UButton* DmgUp;
	UPROPERTY(meta = (BindWidget))
		class UButton* ArmorUp;
	UPROPERTY(meta = (BindWidget))
		class UButton* CritUp;
	UPROPERTY(meta = (BindWidget))
		class UButton* CritDmgUp;
	UPROPERTY(meta = (BindWidget))
		class UButton* HpUp;
	UPROPERTY(meta = (BindWidget))
		class UButton* CoolDownUp;
	UPROPERTY(meta = (BindWidget))
		class UButton* MoveSpeedUp;
	UPROPERTY(meta = (BindWidget))
		class UButton* MaxAmmoUp;

	UPROPERTY(meta = (BindWidget))
		class UButton* Heal;

	UPROPERTY(meta = (BindWidget))
		class UButton* ReloadBtn;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* SpreeCool;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ShotgunCool;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ChannelCool;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ChargeCool;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* Bgm;

	TArray<UObject*> Icons;
	
	TArray<UButton*> Buttons;

	UFUNCTION()
		void PowerUpSpree();
	UFUNCTION()
		void PowerUpShotgun();
	UFUNCTION()
		void PowerUpChannel();
	UFUNCTION()
		void PowerUpCharge();
	UFUNCTION()
		void PowerUpDmg();
	UFUNCTION()
		void PowerUpArmor();
	UFUNCTION()
		void PowerUpCrit();
	UFUNCTION()
		void PowerUpCritDmg();
	UFUNCTION()
		void PowerUpHp();
	UFUNCTION()
		void PowerUpCoolDown();
	UFUNCTION()
		void PowerUpMoveSpeed();
	UFUNCTION()
		void PowerUpMaxAmmo();

	UFUNCTION()
		void PowerUpHeal();

	UFUNCTION()
		void SpreeClicked();
	UFUNCTION()
		void ShotgunClicked();
	UFUNCTION()
		void ChannelClicked();
	UFUNCTION()
		void ChargeClicked();
	UFUNCTION()
		void ReloadClicked();
	void SetPowerUp(UButton* powerUpBtn, int powerNum);

	bool Showitems;
	bool beginRandom;
	bool isStagebg;
	bool isBossbg;
	float Spreecool;
	float Shotguncool;
	float Chargecool;
	float Channelcool;
	int powerNumLeft;
	int powerNumCenter;
	int powerNumRight;
	int levelcount;

public:

	void ShowPowerUps();
	void RandomPowerUps();
	void ClosePowerUps();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativeConstruct() override;
	void BossImfoon(FString Boss);
	void BossImfooff();
};
