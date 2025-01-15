// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogLevelJumper.generated.h"

UCLASS()
class CAP_MOBLIE_API ARogLevelJumper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARogLevelJumper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	class UBoxComponent* ProxBox;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		int LevelDir;
	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void Prox(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//UFUNCTION(BlueprintNativeEvent, Category = Any)
	void LevelJump();

};
