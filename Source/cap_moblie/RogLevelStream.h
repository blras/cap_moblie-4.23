// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/LevelStreaming.h"
#include "RogLevelStream.generated.h"

USTRUCT(BlueprintType)
struct FBoxVolume
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
		class UBoxComponent* BoxVolume;
	FBoxVolume *PreBox;
	FBoxVolume *NextBox;
	
	ULevelStreaming* level;

	int inYaw, outYaw;

	bool isStream;
};
UCLASS()
class CAP_MOBLIE_API ARogLevelStream : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARogLevelStream();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	class UBoxComponent* BoxVolume0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	class UBoxComponent* BoxVolume1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	class UBoxComponent* BoxVolume2;

	bool BoxVol0, BoxVol1, BoxVol2;

	FBoxVolume Box;
	FBoxVolume PreBox;
	FBoxVolume NextBox;
	FBoxVolume mPreBox;
	FBoxVolume mNextBox;

	UFUNCTION(BlueprintNativeEvent, Category = Any)
		void Testap();
	UFUNCTION(BlueprintNativeEvent, Category = Any)
		void LevelStream(int32 leveli, FBoxVolume StreamBox);
	UFUNCTION(BlueprintNativeEvent, Category = Any)
		void InitiateLevelStream();
	UFUNCTION(BlueprintNativeEvent, Category = Any)
		void BackgroundLevelStream(FTransform trans, bool isnext);
	UFUNCTION(BlueprintNativeEvent, Category = Any)
		void LevelStreamOff(int32 leveli);
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	FName levelname;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
	TArray<FName>LevelArray;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	FString spawnname;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	ULevelStreaming* SpawnLevel;

	ULevelStreaming* Prelevel;

	ULevelStreaming* Nextlevel;

	ULevelStreaming* PreBG;
	ULevelStreaming* NextBG;

	ULevelStreaming* StartLv;

	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void Prox(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void PreBoxProx(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//class UDataTable* StageDataTable;
	virtual void Tick(float DeltaTime) override;

private:
	class UDataTable* StageDataTable;
	FVector MapOffset;
	int levelcount;
	int backcount;

};
