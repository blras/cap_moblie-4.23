// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogUserWidget.h"
//#include "Blueprint/UserWidget.h"
#include "RogDamageTextWidget.generated.h"

/**
 * 
 */
UCLASS(abstract)
class CAP_MOBLIE_API URogDamageTextWidget : public URogUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* DmgText;

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	void SetDmgText(FString dmg);
};
