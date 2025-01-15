// Fill out your copyright notice in the Description page of Project Settings.


#include "RogHUD.h"
#include "UserChar.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Widget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/AudioComponent.h"
#include "GameFramework/PlayerController.h"
#include "RogMonk.h"
#include "Engine.h"
#include "Components/Image.h"
#include "Sound/SoundBase.h"
#include "Containers/UnrealString.h"

void URogHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (Spree)
	{
		Spree->OnClicked.AddDynamic(this, &URogHUD::SpreeClicked);
		//Spree->
	}
	if (Shotgun)
	{
		Shotgun->OnClicked.AddDynamic(this, &URogHUD::ShotgunClicked);
	}
	if (Channel)
	{
		Channel->OnClicked.AddDynamic(this, &URogHUD::ChannelClicked);
	}
	if (Charge)
	{
		Charge->OnClicked.AddDynamic(this, &URogHUD::ChargeClicked);
	}
	if (SkillsViewBtn)
	{
		SkillsViewBtn->OnClicked.AddDynamic(this, &URogHUD::ShowPowerUps);
	}
	if (ReloadBtn)
	{
		ReloadBtn->OnClicked.AddDynamic(this, &URogHUD::ReloadClicked);
	}
	Buttons.Add(SpreeUp);
	Buttons.Add(ShotgunUp);
	Buttons.Add(ChannelUp);
	Buttons.Add(ChargeUp);
	Buttons.Add(DmgUp);
	Buttons.Add(ArmorUp);
	Buttons.Add(CritUp);
	Buttons.Add(CritDmgUp);
	Buttons.Add(HpUp);
	Buttons.Add(CoolDownUp);
	Buttons.Add(MoveSpeedUp);
	Buttons.Add(MaxAmmoUp);
	Buttons.Add(Heal);
	SpreeUp->OnClicked.AddDynamic(this, &URogHUD::PowerUpSpree);
	ShotgunUp->OnClicked.AddDynamic(this, &URogHUD::PowerUpShotgun);
	ChannelUp->OnClicked.AddDynamic(this, &URogHUD::PowerUpChannel);
	ChargeUp->OnClicked.AddDynamic(this, &URogHUD::PowerUpCharge);
	DmgUp->OnClicked.AddDynamic(this, &URogHUD::PowerUpDmg);
	ArmorUp->OnClicked.AddDynamic(this, &URogHUD::PowerUpArmor);
	CritUp->OnClicked.AddDynamic(this, &URogHUD::PowerUpCrit);
	CritDmgUp->OnClicked.AddDynamic(this, &URogHUD::PowerUpCritDmg);
	HpUp->OnClicked.AddDynamic(this, &URogHUD::PowerUpHp);
	CoolDownUp->OnClicked.AddDynamic(this, &URogHUD::PowerUpCoolDown);
	MoveSpeedUp->OnClicked.AddDynamic(this, &URogHUD::PowerUpMoveSpeed);
	MaxAmmoUp->OnClicked.AddDynamic(this, &URogHUD::PowerUpMaxAmmo);
	Heal->OnClicked.AddDynamic(this, &URogHUD::PowerUpHeal);
	for (int i = 0; i < Buttons.Num(); i++)
	{
		UObject* obj = Buttons[i]->WidgetStyle.Normal.GetResourceObject();
		Icons.Add(obj);
	}

	Showitems = false;

	Spreecool = 0;
	Shotguncool = 0;
	Chargecool = 0;
	Channelcool = 0;
	powerNumLeft = 0;
	powerNumCenter = 0;
	powerNumRight = 0;
	beginRandom = true;
	isStagebg = false;
	isBossbg = false;
	levelcount = 0;
}

void URogHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

	Super::NativeTick(MyGeometry, InDeltaTime);
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (player != nullptr)
	{
		float hp = player->GetHp();
		float maxhp = player->GetMaxHp();
		float exp = player->GetExp() % 100;
		float nextexp = player->GetNextExp();


		HealthBar->SetPercent(hp / maxhp);
		Experience->SetPercent(exp / nextexp);
		if (player->GetitemView())
		{
			ShowPowerUps();
			player->SetitemView(false);
		}
		if (HealthRed->Percent > HealthBar->Percent)
		{
			HealthRed->SetPercent(HealthRed->Percent - 0.01);
		}
		if (player->Target != nullptr && player->Target->isBoss())
		{
			BossImfoon(player->Target->GetName());
			if (Bgm != nullptr && !isBossbg)
			{
				Bgm->ToggleActive();
				Bgm = UGameplayStatics::SpawnSound2D(this, player->BossBgm);
				isBossbg = true;
				isStagebg = false;
			}
		}
		else
		{
			BossImfooff();
			if (Bgm != nullptr && !isStagebg)
			{
				Bgm->ToggleActive();
				Bgm = UGameplayStatics::SpawnSound2D(this, player->StageBgm);
				isStagebg = true;
				isBossbg = false;
			}
		}
		if (BossName->Visibility == ESlateVisibility::Visible && player->Target != nullptr && player->Target->isBoss())
		{
			float bmaxhp = player->Target->GetMaxHp();
			float bhp = player->Target->GetHp();
			HealthBoss->SetPercent(bhp / bmaxhp);
			float br = Cast<ARogMonk>(player->Target)->GetBreakRate();
			if (br > 200)
			{
				FString b2 = FString::SanitizeFloat(br - 200);
				Break0Rate->SetText(FText::FromString("100"));
				Break1Rate->SetText(FText::FromString("100"));
				Break2Rate->SetText(FText::FromString(b2));
			}
			else if (100 < br && br <= 200)
			{
				Break2E->SetVisibility(ESlateVisibility::Hidden);
				Break2Rate->SetVisibility(ESlateVisibility::Hidden);

				FString b1 = FString::SanitizeFloat(br - 100);
				Break0Rate->SetText(FText::FromString("100"));
				Break1Rate->SetText(FText::FromString(b1));
			}
			else if (0 < br && br <= 100)
			{
				Break2E->SetVisibility(ESlateVisibility::Hidden);
				Break2Rate->SetVisibility(ESlateVisibility::Hidden);

				FString b0 = FString::SanitizeFloat(br);
				Break1Rate->SetText(FText::FromString(b0));
			}
			else
			{
				Break2E->SetVisibility(ESlateVisibility::Hidden);
				Break2Rate->SetVisibility(ESlateVisibility::Hidden);

			}
		}
		SpreeCool->SetPercent(player->GetSkillCooldown(0));
		ShotgunCool->SetPercent(player->GetSkillCooldown(1));
		ChannelCool->SetPercent(player->GetSkillCooldown(2));
		ChargeCool->SetPercent(player->GetSkillCooldown(3));
		Reload->SetPercent(player->GetReloadRate());
		FString ammo = FString::FromInt(player->GetAmmo()) + "/" + FString::FromInt(player->GetMaxAmmo());
		Ammo->SetText(FText::FromString(ammo));


		if (!isBossbg&&!isStagebg)
		{
			Bgm = UGameplayStatics::SpawnSound2D(this, player->StageBgm);
			isStagebg = true;
		}
		if (levelcount!=player->GetLevelCount())
		{
			Bgm->ToggleActive();
			Bgm = UGameplayStatics::SpawnSound2D(this, player->StageBgm);
			levelcount = player->GetLevelCount();
		}
	}
}
void URogHUD::BossImfoon(FString Boss)
{
	BossName->SetText(FText::FromString(Boss));

	HealthBoss->SetVisibility(ESlateVisibility::Visible);
	BossName->SetVisibility(ESlateVisibility::Visible);

	/*Break0E->SetVisibility(ESlateVisibility::Visible);
	Break0Rate->SetVisibility(ESlateVisibility::Visible);
	Break1E->SetVisibility(ESlateVisibility::Visible);
	Break1Rate->SetVisibility(ESlateVisibility::Visible);
	Break2E->SetVisibility(ESlateVisibility::Visible);
	Break2Rate->SetVisibility(ESlateVisibility::Visible);*/
}
void URogHUD::BossImfooff()
{
	HealthBoss->SetVisibility(ESlateVisibility::Hidden);
	BossName->SetVisibility(ESlateVisibility::Hidden);
}
void URogHUD::ShowPowerUps()
{
	if (beginRandom)
	{
		RandomPowerUps();
		beginRandom = false;
	}
	if (!Showitems)
	{
		//PowerUpLeft->SetVisibility(ESlateVisibility::Visible);
		//PowerUpCenter->SetVisibility(ESlateVisibility::Visible);
		//PowerUpRight->SetVisibility(ESlateVisibility::Visible);
		Showitems = true;
	}
	else if (Showitems)
	{
		//ClosePowerUps();
	}
	
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	APlayerController* playercontrollerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	playercontrollerRef->bShowMouseCursor = true;

}
void URogHUD::ClosePowerUps()
{
	Buttons[powerNumLeft]->SetVisibility(ESlateVisibility::Hidden);
	Buttons[powerNumCenter]->SetVisibility(ESlateVisibility::Hidden);
	Buttons[powerNumRight]->SetVisibility(ESlateVisibility::Hidden);
	beginRandom = true;
	APlayerController* playercontrollerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	playercontrollerRef->bShowMouseCursor = false;
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}
void URogHUD::PowerUpSpree()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int skillpoint = player->GetSkillPoint();
	if (skillpoint > 0)
	{
		Spree->SetVisibility(ESlateVisibility::Visible);
		if (player->GetSkillLevel(0) == 0)
			player->BCanSkill(0);
		player->SkillLevelUp(0);
		player->SetSkillPoint(--skillpoint);
		ClosePowerUps();
		if(player->GetSkillPoint()>0)
			RandomPowerUps();
	}

}
void URogHUD::PowerUpShotgun()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int skillpoint = player->GetSkillPoint();
	if (skillpoint > 0)
	{
		Shotgun->SetVisibility(ESlateVisibility::Visible);
		if (player->GetSkillLevel(1) == 0)
			player->BCanSkill(1);
		player->SkillLevelUp(1);
		player->SetSkillPoint(--skillpoint);
		ClosePowerUps();
		if (player->GetSkillPoint() > 0)
			RandomPowerUps();
	}
}
void URogHUD::PowerUpChannel()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int skillpoint = player->GetSkillPoint();
	if (skillpoint > 0)
	{
		Channel->SetVisibility(ESlateVisibility::Visible);
		if (player->GetSkillLevel(2) == 0)
			player->BCanSkill(2);
		player->SkillLevelUp(2);
		player->SetSkillPoint(--skillpoint);
		ClosePowerUps();
		if (player->GetSkillPoint() > 0)
			RandomPowerUps();
	}
}
void URogHUD::PowerUpCharge()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int skillpoint = player->GetSkillPoint();
	if (skillpoint > 0)
	{
		Charge->SetVisibility(ESlateVisibility::Visible);
		if (player->GetSkillLevel(3) == 0)
			player->BCanSkill(3);
		player->SkillLevelUp(3);
		player->SetSkillPoint(--skillpoint);
		ClosePowerUps();
		if (player->GetSkillPoint() > 0)
			RandomPowerUps();
	}
}
void URogHUD::PowerUpDmg()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int skillpoint = player->GetSkillPoint();
	if (skillpoint > 0)
	{
		player->SkillLevelUp(4);
		player->SetSkillPoint(--skillpoint);
		ClosePowerUps();
		if (player->GetSkillPoint() > 0)
			RandomPowerUps();
	}
}
void URogHUD::PowerUpArmor()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int skillpoint = player->GetSkillPoint();
	if (skillpoint > 0)
	{
		player->SkillLevelUp(5);
		player->SetSkillPoint(--skillpoint);
		ClosePowerUps();
		if (player->GetSkillPoint() > 0)
			RandomPowerUps();
	}
}
void URogHUD::PowerUpCrit()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int skillpoint = player->GetSkillPoint();
	if (skillpoint > 0)
	{
		player->SkillLevelUp(6);
		player->SetSkillPoint(--skillpoint);
		ClosePowerUps();
		if (player->GetSkillPoint() > 0)
			RandomPowerUps();
	}
}
void URogHUD::PowerUpCritDmg()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int skillpoint = player->GetSkillPoint();
	if (skillpoint > 0)
	{
		player->SkillLevelUp(7);
		player->SetSkillPoint(--skillpoint);
		ClosePowerUps();
		if (player->GetSkillPoint() > 0)
			RandomPowerUps();
	}
}
void URogHUD::PowerUpHp()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int skillpoint = player->GetSkillPoint();
	if (skillpoint > 0)
	{
		player->SkillLevelUp(8);
		player->SetSkillPoint(--skillpoint);
		ClosePowerUps();
		if (player->GetSkillPoint() > 0)
			RandomPowerUps();
	}
}
void URogHUD::PowerUpCoolDown()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int skillpoint = player->GetSkillPoint();
	if (skillpoint > 0)
	{
		player->SkillLevelUp(9);
		player->SetSkillPoint(--skillpoint);
		ClosePowerUps();
		if (player->GetSkillPoint() > 0)
			RandomPowerUps();
	}
}
void URogHUD::PowerUpMoveSpeed()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int skillpoint = player->GetSkillPoint();
	if (skillpoint > 0)
	{
		player->SkillLevelUp(10);
		player->SetSkillPoint(--skillpoint);
		ClosePowerUps();
		if (player->GetSkillPoint() > 0)
			RandomPowerUps();
	}
}
void URogHUD::PowerUpMaxAmmo()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int skillpoint = player->GetSkillPoint();
	if (skillpoint > 0)
	{
		player->SkillLevelUp(11);
		player->SetSkillPoint(--skillpoint);
		ClosePowerUps();
		if (player->GetSkillPoint() > 0)
			RandomPowerUps();
	}
}
void URogHUD::PowerUpHeal()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int skillpoint = player->GetSkillPoint();
	int hp = player->GetHp();
	int mph = player->GetMaxHp();
	hp = hp + 100;
	if (hp > mph)
		hp = mph;
	player->Hp = hp;
	player->SetSkillPoint(--skillpoint);
	ClosePowerUps();
	if (player->GetSkillPoint() > 0)
		RandomPowerUps();
}
void URogHUD::SetPowerUp(UButton* powerUpBtn, int powerNum)
{
	auto Slot = Cast<UCanvasPanelSlot>(powerUpBtn->Slot);
	auto btn = Cast<UCanvasPanelSlot>(Buttons[powerNum]->Slot);
	Buttons[powerNum]->SetVisibility(ESlateVisibility::Visible);
	btn->SetPosition(Slot->GetPosition());
}
void URogHUD::SpreeClicked()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	player->Spree();
}
void URogHUD::ShotgunClicked()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	player->Shotgun();
}
void URogHUD::ChannelClicked()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	player->Channeling();
}
void URogHUD::ChargeClicked()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	player->Charge();
}
void URogHUD::ReloadClicked()
{
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	player->Reloading();
}
void URogHUD::RandomPowerUps()
{
	TArray<int> powers = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };
	for (int i = 0; i < 3; i++)
	{
		int k = FMath::RandRange(0, powers.Num()-1);
		switch (i)
		{
		case 0:SetPowerUp(PowerUpLeft, powers[k]); powerNumLeft = powers[k]; break;
		case 1:SetPowerUp(PowerUpCenter, powers[k]); powerNumCenter = powers[k];  break;
		case 2:SetPowerUp(PowerUpRight, powers[k]); powerNumRight = powers[k];  break;
		}
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(k));
		powers.RemoveAt(k);
	}
}