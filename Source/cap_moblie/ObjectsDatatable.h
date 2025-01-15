// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Materials/Material.h"
#include "ObjectsDatatable.generated.h"

USTRUCT(BlueprintType)
struct FObjectsTableRow : public FTableRowBase
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objects")
		TSoftObjectPtr<UStaticMesh> EnviromentPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objects")
		TSoftObjectPtr<UStaticMesh> ObjectsPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objects")
		TSoftObjectPtr<UStaticMesh> BridgePath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objects")
		TSoftObjectPtr<UStaticMesh> BackgroudPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objects")
		TSoftObjectPtr<UMaterial> EnvMatPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objects")
		TSoftObjectPtr<UMaterial> ObjMatPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objects")
		TSoftObjectPtr<UMaterial> BrgMatPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objects")
		TSoftObjectPtr<UMaterial> BgMatPath;
};
UCLASS()
class CAP_MOBLIE_API AObjectsDatatable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectsDatatable();
};
