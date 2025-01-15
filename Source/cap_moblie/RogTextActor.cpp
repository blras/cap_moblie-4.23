// Fill out your copyright notice in the Description page of Project Settings.


#include "RogTextActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/WidgetComponent.h"
#include "RogDamageTextWidget.h"

// Sets default values
ARogTextActor::ARogTextActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget>textblock(TEXT("/Game/Blueprints/widgetbp/bp_RogDamageText"));


	TextWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("RogDamageText"));
	TextWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TextWidgetComp->RelativeLocation = FVector(0, 0, 180);

	if (textblock.Succeeded())
		TextWidgetComp->SetWidgetClass(textblock.Class);

	TextWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	TextWidgetComp->SetDrawAtDesiredSize(true);
	TextWidgetComp->SetVisibility(true);

	delta = 40;
}

// Called when the game starts or when spawned
void ARogTextActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARogTextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (delta <= 0)
		Destroy();
	else
	{
		delta--;
		SetActorLocation((GetActorLocation()+FVector(0,0,1)));
	}
	//URogDamageTextWidget* dmg = Cast<URogDamageTextWidget>(TextWidgetComp->GetUserWidgetObject());
	//dmg->SetDmgText("dmg");
}
void ARogTextActor::SetText(FString str)
{
	URogDamageTextWidget* dmg = Cast<URogDamageTextWidget>(TextWidgetComp->GetUserWidgetObject());
	dmg->SetDmgText(str);
}
