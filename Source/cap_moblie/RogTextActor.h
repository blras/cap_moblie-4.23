// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogTextActor.generated.h"

UCLASS()
class CAP_MOBLIE_API ARogTextActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARogTextActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* TextWidgetComp;

private:
	int32 delta;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetText(FString str);

};
