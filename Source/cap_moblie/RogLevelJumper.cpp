// Fill out your copyright notice in the Description page of Project Settings.

#include "RogLevelJumper.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine.h"
#include "UserChar.h"
// Sets default values
ARogLevelJumper::ARogLevelJumper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProxBox= CreateDefaultSubobject<UBoxComponent>(FName("ProxBox"));
	ProxBox->SetupAttachment(RootComponent);
	ProxBox->SetWorldScale3D(FVector(90, 1, 20));
	ProxBox->OnComponentBeginOverlap.AddDynamic(this, &ARogLevelJumper::Prox);
	LevelDir = 1;
}

// Called when the game starts or when spawned
void ARogLevelJumper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARogLevelJumper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARogLevelJumper::LevelJump()
{

}
void ARogLevelJumper::Prox_Implementation(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	int level = FMath::RandRange(0, 6);
	level = 0;
	if (Cast<AUserChar>(OtherActor))
	{
		switch (LevelDir)
		{
		case 0: UGameplayStatics::OpenLevel(this, (TEXT("TestDungeon"))); break;
		case 1: UGameplayStatics::OpenLevel(this, (TEXT("forestbossTest"))); break;
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString(TEXT("jump!")));
	
}