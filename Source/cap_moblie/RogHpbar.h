// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RogHpbar.generated.h"

/**
 * 
 */
UCLASS(abstract)
class CAP_MOBLIE_API URogHpbar : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthRed;
private:
	int32 Hp;
	int32 MaxHp;
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	int GetHp();
	int GetMaxHp();
	void SetHp(int hp);
	void SetMaxHp(int Maxhp);
};
