// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class CAP_MOBLIE_API AItem : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	 AItem();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* ItemMeshComponent;
private:
	uint32 bCanDmg : 1;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool IsUse;
	float AttackRate;
	int32 range;
	FString faction;
	UFUNCTION(BlueprintNativeEvent, Category = Any)
	void Setting();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	class USphereComponent* HitSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	class USphereComponent* ProxSphere;
	UFUNCTION(BlueprintNativeEvent, Category = Any)
	void CanDmg();
	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void Prox(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void HitBox(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
