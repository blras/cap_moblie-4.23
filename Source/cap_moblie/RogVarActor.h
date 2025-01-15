// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogVarActor.generated.h"

USTRUCT(BlueprintType)
struct FStageData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
	int StageNum;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
	TArray<FVector>EnvLocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
	TArray<FVector>ObjectLocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
	TArray<UStaticMesh*>ObjectMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
	TArray<UStaticMesh*>EnvMesh;

	//TArray<FRotator>EnvRotator;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
	TArray<FRotator>ObjectRotator;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
	TArray<FRotator>EnvRotator;
};

UCLASS()

class CAP_MOBLIE_API ARogVarActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ARogVarActor();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
	TArray<UStaticMesh*>ObjectMeshPath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
	TArray<UStaticMesh*>EnvMeshPath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
	TArray<FStageData>Stages;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetStageSetting(int num);
	void SettingObjects(FString &info,int num);
	void SettingEnvs(FString& info, int num);
	void SetObjectLocation(int num);
	void SetEnvLocation(int num);
	void SetObjectRotator(int num);
	void SetEnvRotator(int num);
private:
	class UDataTable* ObjectDataTable;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintNativeEvent, Category = Any)
	void GetVarMesh(int num);
	//UFUNCTION(BlueprintNativeEvent, Category = Any)
	//void GetVarMesh(int num);
	FORCEINLINE class TArray<UStaticMesh*> GetObjectMeshPath() const { return ObjectMeshPath; }
};
