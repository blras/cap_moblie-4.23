// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Cap_AIController.generated.h"

/**
 * 
 */
UCLASS()
class CAP_MOBLIE_API ACap_AIController : public AAIController
{
	GENERATED_BODY()
public:
	ACap_AIController();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UBehaviorTree* BehaviorTree;
	//UPROPERTY(Category = AIPerception, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionComponent* AIPerceptionComponent;
	class UAISenseConfig_Sight* SightConfig;
	class UAISenseCongig_Damage* DamageConfig;
	class UAISenseCongig_Hearing* HearingConfig;
public:
	//virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintNativeEvent, Category = Any)
	void SenseStuff(AActor *Actor, FAIStimulus Stimulus);
	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void SenseStuffs(const TArray<AActor*>& UpdatedActors);
	//FORCEINLINE class UAIPerceptionComponent* GetAIPerceptionComponent() const { return AIPerceptionComponent; }
};
