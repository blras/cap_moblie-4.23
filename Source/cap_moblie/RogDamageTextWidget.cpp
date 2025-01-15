// Fill out your copyright notice in the Description page of Project Settings.


#include "RogDamageTextWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void URogDamageTextWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
}
void URogDamageTextWidget::SetDmgText(FString dmg)
{
	DmgText->SetText(FText::FromString(dmg));
}