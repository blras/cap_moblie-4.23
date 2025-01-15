// Fill out your copyright notice in the Description page of Project Settings.


#include "RogHpbar.h"
#include "RogCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"



void URogHpbar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if ((this->IsVisible()))
	{
		float hp = Hp;
		float maxhp = MaxHp;
		if (maxhp > 0)
		{
			HealthBar->SetPercent(hp / maxhp);
			if (HealthRed->Percent > HealthBar->Percent)
			{
				HealthRed->SetPercent(HealthRed->Percent - 0.01);
			}
		}
	}
}
int URogHpbar::GetHp()
{
	return Hp;
}
int URogHpbar::GetMaxHp()
{
	return MaxHp;
}
void URogHpbar::SetHp(int hp)
{
	Hp = hp;
}
void URogHpbar::SetMaxHp(int Maxhp)
{
	MaxHp = Maxhp;
}