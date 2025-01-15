// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogStage.generated.h"

UCLASS()
class CAP_MOBLIE_API ARogStage : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ARogStage();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
	TArray<FVector>ObjectLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	class USphereComponent* SphereComp;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float Length;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	int MAXEnemy;
public:	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	bool spawn;
	//UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	//int ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Any)
	TArray<AActor*>CharacterinStage;


	UFUNCTION(BlueprintNativeEvent, Category = Any)
	void SpawnEnemy();

	UFUNCTION(BlueprintNativeEvent, Category = Any)
	void SpawnObject();

	FTimerHandle MemberTimerHandle;

};
