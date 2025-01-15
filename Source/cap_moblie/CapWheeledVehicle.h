// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "CapWheeledVehicle.generated.h"

/**
 * 
 */
UCLASS()
class CAP_MOBLIE_API ACapWheeledVehicle : public AWheeledVehicle
{
	GENERATED_BODY()

public:
	ACapWheeledVehicle();
protected:
	//virtual void BeginPlay() override;
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* MeshComponent;

	//class 

public:
	UFUNCTION(BlueprintNativeEvent, Category = Any)
	void Move();
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE class USkeletalMeshComponent* GetMeshComponent() const { return MeshComponent; }
};
