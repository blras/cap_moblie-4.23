// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogObject.generated.h"

UCLASS()
class CAP_MOBLIE_API ARogObject : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ObjectMeshComponent;


public:	
	// Sets default values for this actor's properties
	ARogObject();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
	TArray<UStaticMesh*>ObjectMeshPath;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	int Type;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintNativeEvent, Category = Any)
	void SetObjectType(int num);
	FORCEINLINE class UStaticMeshComponent* GetObjectMeshComponent() const { return ObjectMeshComponent; }
};
