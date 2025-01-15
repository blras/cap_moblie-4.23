// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "cap_DataTableGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CAP_MOBLIE_API Acap_DataTableGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	Acap_DataTableGameModeBase();
	virtual void BeginPlay() override;

private:
	class UDataTable* ObjectDataTable;
};
