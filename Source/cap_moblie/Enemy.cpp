// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/CollisionProfile.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "UserChar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Item.h"
#include "Gun.h"
#include "RogEnemyActor.h"
#include "RogHpbar.h"
#include "RogEffect.h"
#include "EngineUtils.h"
#include "Cap_AIController.h"
#include "Particles/ParticleSystem.h"
#include "Engine.h"
#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationPath.h"
#include "UserChar.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Mesh(TEXT("/Game/meshes/Characters/SK_Character_DarkElf_01"));
	// Create the mesh component
	MeshComponent->SetSkeletalMesh(Mesh.Object);
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	MeshComponent->SetWorldScale3D(FVector(1, 1, 1));
	MeshComponent->RelativeRotation = FRotator(0.f, -90.f, 0.f);
	MeshComponent->RelativeLocation = FVector(0, 0, -90);
	MeshComponent->SetGenerateOverlapEvents(true);
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem>teleporteffect(TEXT("/Game/Particles/ParticleSystems/P_Trail_Fire"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> teleportmontage(TEXT("/Game/polymonk/Torn_Space_intro_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> healmontage(TEXT("/Game/polyStaff/skill16_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> resurrectmontage(TEXT("/Game/polyStaff/skill12_Montage"));

	static ConstructorHelpers::FObjectFinder<USoundBase>teleportsound(TEXT("/Game/Sounds/Character/Boss/2_forest_Boss/e102_Torn_Space_intro"));

	if (teleportmontage.Object)
		TeleportAnimmontage = teleportmontage.Object;
	if (healmontage.Object)
		HealAnimmontage = healmontage.Object;
	if (resurrectmontage.Object)
		ResurrectAnimmontage = resurrectmontage.Object;
	if (teleportsound.Object != nullptr)
		TeleportSound = teleportsound.Object;
	if (teleporteffect.Object != nullptr)
		TeleportEffect = teleporteffect.Object;

	HitBox = CreateDefaultSubobject<UBoxComponent>(FName("HitBox"));
	HitBox->RelativeLocation = FVector(0,0,0);
	HitBox->RelativeRotation = FRotator(0,0,0);
	HitBox->InitBoxExtent(FVector(16, 16, 32));
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnAttack);
	FName handsocket = TEXT("Hand_R");
	WeaponComponent->SetupAttachment(MeshComponent, handsocket);
	Hp = 500;
	MoveSpeed = 300;
	HasHpRegen = false;
	HasTel = false;
	bCanTel = false;
	HasHeal = false;
	bCanHeal = false;
	HasCastResurrect = false;
	bCastResurrect = false;
	Level = 1;
	faction = "Enemy";
	EnemyNum = -1;
	AIControllerClass = ACap_AIController::StaticClass();
	//GoalLoation = FVector(0,0,0);
	range = 200;

	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	GoalLoation = GetActorLocation();
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Level = player->Level;
	SetEnemy();
	isboss = false;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{   
	Super::Tick(DeltaTime);
	if (HasHpRegen)
		HpRegeneration();
	if (Hp <= 0&&live)
	{
		//Destroy();
		Death();
	}
	else if (Hp>0 && live)
	{
		//Sight();
		if (bCanFire == true)
		{
			Move();
		}
		if (HasTel&&bCanTel&&Target!=nullptr)
		{
			Teleport();
		}
		if (HasHeal && bCanHeal && FTarget != nullptr)
			Heal();
		if (HasCastResurrect && bCastResurrect && CTarget != nullptr)
			CastResurrect();
	}
	if (FTarget != nullptr)
		if (!FTarget->isLive())
			CTarget = FTarget;
}
void AEnemy::SetStat()
{
	Hp = Hp + Level * 5;
	MaxHp = Hp;
	Dmg = 3 + Level * 5;
}
void AEnemy::SetEnemy()
{
	ARogEnemyActor* Var;
	int envitr = 0;
	UWorld* const World = GetWorld();
	for (TActorIterator<ARogEnemyActor>Itr(World); Itr; ++Itr)
	{
		Var = *Itr;
		envitr = Var->Getenvitr();
		if(EnemyNum<0)
			EnemyNum = FMath::RandRange(0, ((envitr+1)*4));

		int type;
		USkeletalMesh *mesh;
		USkeletalMesh* weapon;
		UClass* anim;
		UAnimMontage* montage;
		UAnimMontage* deathmontage;
		UParticleSystem* bulleteffect;
		UParticleSystem* hiteffect;
		
		mesh = Var->CharacterMeshPath[EnemyNum];
		weapon = Var->WeaponMeshPath[EnemyNum];
		anim = Var->AnimPath[EnemyNum];
		montage = Var->MontagePath[EnemyNum];
		deathmontage = Var->DeathMontagePath[EnemyNum];
		type = Var->Type[EnemyNum];
		bulleteffect = Var->EffectPath[EnemyNum];
		hiteffect = Var->HitEffectPath[EnemyNum];
		float size = Var->Size[EnemyNum];

		USoundBase* sound = Var->AttackSound[EnemyNum];
		USoundBase* deathsound = Var->DeathSoundPath[EnemyNum];
		if (mesh != nullptr)
		{
			MeshComponent->SetSkeletalMesh(mesh);
		}
		if (bulleteffect != nullptr)
		{
			BulletEffect = bulleteffect;
		}
		if (hiteffect != nullptr)
		{
			HitEffect = hiteffect;
		}
		if (weapon != nullptr)
		{
			WeaponComponent->SetSkeletalMesh(weapon);
			FName handsocket = TEXT("Hand_R");
			FVector location = FVector(0,0,0);
			FRotator rotation = FRotator(0, 0, 0);
			switch (type)
			{
			case 0:
				handsocket = TEXT("Hand_L");
				location = FVector(4, 0, -10);
				rotation = FRotator(-28, 78, -27);
				break;
			case 1:
				handsocket = TEXT("Hand_L");
				location = FVector(10, 3, 0);
				rotation = FRotator(0, -180, 0);
				WeaponComponent->SetWorldScale3D(FVector(0.4, 0.4, 0.4));
				break;
			case 2:
				HitBox->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepWorldTransform, handsocket);
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				handsocket = TEXT("Hand_R");
				location = FVector(-8, 0, 0);
				rotation = FRotator(0, 0, 180);
				break;
			case 6:
				handsocket = TEXT("Hand_R");
				location = FVector(-6, -4, 6);
				rotation = FRotator(200,90,30);
				break;
			}
			if (sound != nullptr)
			{
				AttackSound = sound;
			}
			WeaponComponent->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepWorldTransform, handsocket);
			WeaponComponent->RelativeLocation = location;
			WeaponComponent->RelativeRotation = rotation;
			HitBox->AttachToComponent(WeaponComponent, FAttachmentTransformRules::KeepWorldTransform);
			HitBox->RelativeRotation = FRotator(0,0,0);
			HitBox->RelativeLocation = location;
		}
		else if (type == 2)
		{
			FName handsocket = TEXT("Hand_R");
			HitBox->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepWorldTransform, handsocket);
			HitBox->RelativeRotation = FRotator(0, 0, 0);
			HitBox->RelativeLocation = FVector(0,0,0);
			if (sound != nullptr)
			{
				AttackSound = sound;
			}
		}

		if (anim !=nullptr)
		{
			MeshComponent->SetAnimInstanceClass(anim);
		}
		DeathSound = deathsound;
		Animmontage = montage;
		Deathmontage = deathmontage;
		range = Var->Range[EnemyNum];
		Hp = Var->Hp[EnemyNum]+Level*5;
		MoveSpeed = Var->Speed[EnemyNum]*150;
		Dmg = 3 +Level*Var->Dmg[EnemyNum];
		GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
		AttackRate = Var->DmgRate[EnemyNum];
		MaxHp = Hp;
		SetActorScale3D(FVector(size, size, size));
		if (EnemyNum == 5 || EnemyNum == 17)
			HasHpRegen = true;
		if (EnemyNum == 13 || EnemyNum == 14 || EnemyNum ==19|| EnemyNum ==21|| EnemyNum ==22)
		{
			HasTel = true;
			bCanTel = true;
		}
		if (EnemyNum < 13&&EnemyNum>10)
		{
			HasCastResurrect = true;
			bCastResurrect = true;
		}
	}
	if (range <= 200)
	{
		FVector dmglo = FVector(0, 0, range/2);
		HitBox->RelativeLocation = dmglo;
		
	}
	//MaxHp = 100;
	//Hp = 100;
	HpbarRef->SetHp(Hp);
	HpbarRef->SetMaxHp(MaxHp);
}
// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnAttack_Implementation(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bCanFire == false)
	{
		if (bCanDmg == true)
		{
			if (Cast<AUserChar>(OtherActor) == nullptr ||Target == nullptr)
			{
				return;
			}
			Target->HitDamage(10, GetActorLocation());
			bCanDmg = false;
		}
	}
}

void AEnemy::Sight_Implementation()
{
	FHitResult hit;
	FVector strace = GetActorLocation() + (GetActorForwardVector() * 60);
	FVector etrace = strace + (GetActorForwardVector() * 1500);
	GetWorld()->LineTraceSingleByObjectType(hit, strace, etrace, ECollisionChannel::ECC_Pawn);
	if (hit.GetActor() == nullptr)
	{
		return;
	}
	else
	{
		if (Cast<AUserChar>(hit.GetActor()) == nullptr)
		{
			return;
		}
		Target = Cast<AUserChar>(hit.GetActor());
	}
}

void AEnemy::OnTarget_Implementation(AActor* Actors)
{
	Target =Cast<AUserChar>(Actors);
}
void AEnemy::Hearing_Implementation()
{
}
void AEnemy::Move_Implementation()
{
	FVector Movement;
	if (Target != nullptr)
	{
		Movement = Target->GetActorLocation() - GetActorLocation();
		GoalLoation = Target->GetActorLocation();
		UWorld *const World = GetWorld();
		
		AAIController *controller = Cast<AAIController>(GetController());

		UNavigationSystemV1* navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
		UNavigationPath* path = navSys->FindPathToLocationSynchronously(GetWorld(), Target->GetActorLocation(), GetActorLocation(), NULL);
		if (Movement.Size() >= range)
		{
			//controller->MoveToActor(Target, (20));
			Movement.GetClampedToMaxSize(1);
			SetActorRotation(Movement.Rotation());
			AddMovementInput(Movement, 1);
			//controller->MoveToActor(Target, (range - 50), true, false);
		}
		else
		{
			FVector gunoffset = FVector(30, 0, 0);
			Attack(Movement,gunoffset);
		}
	}
	/*if (GoalLoation != GetActorLocation())
	{
		Movement = GoalLoation - GetActorLocation();
		if (Movement.Size() > range) 
		{
			Movement.GetClampedToMaxSize(1);
			FRotator Rotation = FRotator(0, Movement.Rotation().Yaw, 0);
			SetActorRotation(Rotation);
			AddMovementInput(Movement, MoveSpeed);
		}
	}*/
}
void AEnemy::HpRegeneration()
{
	Hp += 0.01;
}
void AEnemy::Teleport()
{
	UWorld* const World = GetWorld();
	FVector gunoffset = FVector(0, 0, 0);
	FVector Movement = FVector(0, 0, 0);
	if (World != NULL)
	{
		UWorld* const World = GetWorld();
		const FRotator FireRotation = Movement.Rotation();
		const FVector SpawnLocation = GetActorLocation();
		ARogEffect* effect;
		// spawn the projectile
		effect = World->SpawnActor<ARogEffect>(SpawnLocation + FireRotation.RotateVector(gunoffset), FireRotation);
		if (TeleportEffect != nullptr)
			effect->SetParticle(TeleportEffect);
	}
	PlayAnimMontage(TeleportAnimmontage, 1);
	UGameplayStatics::PlaySoundAtLocation(this, TeleportSound, GetActorLocation());
	if (Target != nullptr)
	{
		Movement = Target->GetActorLocation() - GetActorLocation();
		//Movement.GetClampedToMaxSize(1);
		//FVector launchdir = Movement + FVector(0, 0, 1200);
		float X = FMath::RandRange(-range/2, range/2);
		float Y = FMath::RandRange(-range/2, range/2);
		SetActorLocation(GetActorLocation() + Movement + FVector(X,Y,0));
	}
	if (World != NULL)
	{
		UWorld* const World = GetWorld();
		const FRotator FireRotation = Movement.Rotation();
		const FVector SpawnLocation = GetActorLocation();
		ARogEffect* effect;
		// spawn the projectile
		effect = World->SpawnActor<ARogEffect>(SpawnLocation + FireRotation.RotateVector(gunoffset), FireRotation);
		if (TeleportEffect != nullptr)
			effect->SetParticle(TeleportEffect);
	}
	World->GetTimerManager().SetTimer(TimerHandle_TeleportTimerExpired, this, &AEnemy::TeleportCool, 10);
	bCanTel = false;
}
void AEnemy::TeleportCool()
{
	bCanTel = true;
}
void AEnemy::Heal()
{
	UWorld* const World = GetWorld();
	if (FTarget != nullptr)
	{
		if (FTarget->GetHp() != FTarget->GetMaxHp())
		{
			if (FTarget->GetHp() + 20 < FTarget->GetMaxHp())
				FTarget->Hp = FTarget->GetHp() + 20;
			else
				FTarget->Hp = FTarget->GetMaxHp();
			World->GetTimerManager().SetTimer(TimerHandle_HealTimerExpired, this, &AEnemy::HealCool, 15);
			bCanHeal = false;
			PlayAnimMontage(HealAnimmontage, 1);
		}
	}
}
void AEnemy::HealCool()
{
	bCanHeal = true;
}
void AEnemy::CastResurrect()
{
	UWorld* const World = GetWorld();
	FVector gunoffset = FVector(0, 0, 0);
	if (CTarget != nullptr)
	{
		if (!CTarget->isLive()&&!CTarget->GetResurrect())
		{
			CTarget->SetResurrect(true);
			World->GetTimerManager().SetTimer(TimerHandle_CResurrectTimerExpired, this, &AEnemy::CastResurrectCool, 25);
			bCastResurrect = false;
			PlayAnimMontage(ResurrectAnimmontage, 1);
			if (World != NULL)
			{
				UWorld* const World = GetWorld();
				const FRotator FireRotation = CTarget->GetActorRotation();
				const FVector SpawnLocation = CTarget->GetActorLocation();
				ARogEffect* effect;
				// spawn the projectile
				effect = World->SpawnActor<ARogEffect>(SpawnLocation + FireRotation.RotateVector(gunoffset), FireRotation);
				if (ResurrectEffect != nullptr)
					effect->SetParticle(ResurrectEffect);
				UGameplayStatics::PlaySoundAtLocation(this, ResurrectSound, GetActorLocation());
			}
		}
	}
}
void AEnemy::CastResurrectCool()
{
	bCastResurrect = true;
}
void AEnemy::SetEnemyNum(int n)
{
	EnemyNum = n;
	SetEnemy();
}