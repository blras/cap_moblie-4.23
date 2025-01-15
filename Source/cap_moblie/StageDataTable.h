// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "StageDataTable.generated.h"

USTRUCT(BlueprintType)
struct FStageTableRow : public FTableRowBase
{
	GENERATED_BODY();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Z;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString InYaw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString OutYaw;
};
UCLASS()
class CAP_MOBLIE_API AStageDataTable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStageDataTable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
