// Fill out your copyright notice in the Description page of Project Settings.


#include "Cap_AIController.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Enemy.h"
#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "UserChar.h"
#include "Engine.h"

ACap_AIController::ACap_AIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AIBehaviorFinder(TEXT("BehaviorTree'/Game/NPC/NPC_BT.NPC_BT'"));
	if (AIBehaviorFinder.Object)
	{
		BehaviorTree = AIBehaviorFinder.Object;
	}
	PerceptionComponent = GetAIPerceptionComponent();
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	SightConfig->SightRadius = 2100;
	SightConfig->LoseSightRadius = (6300);
	SightConfig->PeripheralVisionAngleDegrees = 180.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	PerceptionComponent->ConfigureSense(*SightConfig);
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, SightConfig->GetSenseImplementation(), GetPawn());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &ACap_AIController::SenseStuffs);
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ACap_AIController::SenseStuff);


	//HearingConfig = CreateDefaultSubobject<UAISenseCongig_Hearing>(TEXT("Hearing Config"));
	//PerceptionComponent->ConfigureSense(*HearingConfig);
	//PerceptionComponent->SetDominantSense(HearingConfig->GetSenseImplementation());
	/*SightConfig->SightRadius = 3000;
	SightConfig->LoseSightRadius = (3500);
	SightConfig->PeripheralVisionAngleDegrees = 60.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	PerceptionComponent->ConfigureSense(*SightConfig);
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, SightConfig->GetSenseImplementation(), GetPawn());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &ACap_AIController::SenseStuffs);
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ACap_AIController::SenseStuff);*/
}
void ACap_AIController::BeginPlay()
{
	Super::BeginPlay();
	//RunBehaviorTree(BehaviorTree);
}
void ACap_AIController::SenseStuff_Implementation(AActor *Actor, FAIStimulus Stimulus)
{
	//AUserChar* target;
	//AEnemy* Ftarget;
	//if (Cast<AUserChar>(Actor) != nullptr)
		//target = Cast<AUserChar>(Actor);
	AUserChar* target = Cast<AUserChar>(Actor);
	//else if (Cast<AEnemy>(Actor) != nullptr)
		//Ftarget = Cast<AEnemy>(Actor);
	AEnemy* Ftarget = Cast<AEnemy>(Actor);
	AEnemy* Ctarget = Cast<AEnemy>(Actor);
	FVector targetlocation = target->GetActorLocation();
	//Blackboard->SetValueAsBool(FName(TEXT("CanSeePlayer")), true);
	ARogCharacter* ControlledPawn = Cast<ARogCharacter>(GetPawn());
	if(ControlledPawn->Target == nullptr && target!=nullptr)
		ControlledPawn->Target = target;
	if (Ftarget != nullptr)
	{
		if(Ftarget->isLive())
			ControlledPawn->FTarget = Ftarget;
	}
	//if (Ctarget != nullptr)
	//{
		//if(!Ctarget->isLive())
			//ControlledPawn->CTarget = Ctarget;
	//}
		//UWorld* const World = GetWorld();
		//UNavigationSystemV1* navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
		//UNavigationPath* path = navSys->FindPathToLocationSynchronously(GetWorld(), target->GetActorLocation(), ControlledPawn-> GetActorLocation(), NULL);

		
}
void ACap_AIController::SenseStuffs_Implementation(const TArray<AActor*>& UpdatedActors)
{
}
