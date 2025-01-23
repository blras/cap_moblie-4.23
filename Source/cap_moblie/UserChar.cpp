// Fill out your copyright notice in the Description page of Project Settings.


#include "UserChar.h"
#include "cap_moblieProjectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Enemy.h"
#include "RogHUD.h"
#include "Engine.h"
#include "Bullet.h"
#include "Bomb.h"
#include "RogHpbar.h"
#include "RogExplosionActor.h"


const FName AUserChar::MoveForwardBinding("MoveForward");
const FName AUserChar::MoveRightBinding("MoveRight");
const FName AUserChar::LookForwardBinding("LookForward");
const FName AUserChar::TurnRightBinding("TurnRight");

// Sets default values
AUserChar::AUserChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> UserMesh(TEXT("/Game/Meshes/Characters/SK_Character_Rock_Golem"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimFinder(TEXT("Class'/Game/polytwin/polytwinbp/Twinblast_AnimBlueprint.Twinblast_AnimBlueprint_C'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("/Game/Meshes/Weapons/Arsenal/smg2_d_sm"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> GWeaponMesh(TEXT("/Game/Meshes/Weapons/Arsenal/shotgun_d_sm"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> G1WeaponMesh(TEXT("/Game/Meshes/Weapons/SK_Wep_Goblin_Gem_Hammer_01"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>bulleteffect(TEXT("/Game/Particles/Projectiles/P_Projectile_Bullet01Blue"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>hiteffect(TEXT("/Game/Particles/Muzzles/P_Muzzle_Bullet01Blue"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>chargeeffect(TEXT("/Game/Particles/Projectiles/P_Projectile_Plasma02Blue"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>chargehiteffect(TEXT("/Game/Particles/Muzzles/P_Muzzle_Plasma02Blue"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>channeleffect(TEXT("/Game/Particles/Fx/Candle_Fire"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>channelhiteffect(TEXT("/Game/Particles/Fx/Hit"));

	static ConstructorHelpers::FObjectFinder<USoundBase>shotsound(TEXT("/Game/Sounds/Character/Player_Character_(Finish)/c1_Attack"));
	static ConstructorHelpers::FObjectFinder<USoundBase>hitsound(TEXT("/Game/Sounds/Character/Player_Character_(Finish)/c1_Dead"));
	static ConstructorHelpers::FObjectFinder<USoundBase>flamesound(TEXT("/Game/Sounds/Audio/Fire01"));
	static ConstructorHelpers::FObjectFinder<USoundBase>chargesound(TEXT("/Game/Sounds/Audio/Light02"));
	static ConstructorHelpers::FObjectFinder<USoundBase>chargeshotsound(TEXT("/Game/Sounds/Character/Player_Character_(Finish)/e106_skill6__2_"));
	static ConstructorHelpers::FObjectFinder<USoundBase>shotgunsound(TEXT("/Game/Sounds/Audio/Explosion01"));
	static ConstructorHelpers::FObjectFinder<USoundBase>spreesound(TEXT("/Game/Sounds/Character/Player_Character_(Finish)/e106_skill16"));

	static ConstructorHelpers::FObjectFinder<USoundBase>oasisbg(TEXT("/Game/Sounds/Map/02_Oasis"));
	static ConstructorHelpers::FObjectFinder<USoundBase>fairybg(TEXT("/Game/Sounds/Map/04_Fairy"));
	static ConstructorHelpers::FObjectFinder<USoundBase>dampbg(TEXT("/Game/Sounds/Map/06_Damp"));
	static ConstructorHelpers::FObjectFinder<USoundBase>tensionbg(TEXT("/Game/Sounds/Map/08_Tension"));

	// Create the mesh component
	GWeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("GWeaponComponent"));

	MeshComponent->SetSkeletalMesh(UserMesh.Object);
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	MeshComponent->SetWorldScale3D(FVector(1, 1, 1));

	LeftWeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("LeftWeaponComponent"));
	LeftWeaponComponent->SetSkeletalMesh(WeaponMesh.Object);
	if (AnimFinder.Object)
	{
		UClass* Anim = AnimFinder.Object;
		MeshComponent->SetAnimInstanceClass(Anim);
	}
	MeshComponent->RelativeRotation = FRotator(0.f, -90.f, 0.f);
	MeshComponent->RelativeLocation = FVector(0, 0, -90);
	WeaponComponent->SetSkeletalMesh(WeaponMesh.Object);
	if(GWeaponMesh.Object)
		GWeaponComponent->SetSkeletalMesh(GWeaponMesh.Object);
	static ConstructorHelpers::FObjectFinder<UAnimMontage> animmontage(TEXT("/Game/polytwin/Primary_Fire_Med_A_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> animmontageLeft(TEXT("/Game/polytwin/DoubleShot_Fire_Lft_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> animmontageRight(TEXT("/Game/polytwin/DoubleShot_Fire_Rt_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> animmontageShotgun(TEXT("/Game/polyRifle/Fire_NoReload_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> animmontageCharge(TEXT("/Game/polyRifle/TheEleven_UpperBody_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> animmontageChargeShot(TEXT("/Game/polytwin/Ability_ChargeBlast_Fire_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> animmontageChannel(TEXT("/Game/polytwin/Ability_Ultimate_Fire_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> animmontageChannelStart(TEXT("/Game/polytwin/Ability_Ultimate_Start_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> animmontageChannelEnd(TEXT("/Game/polytwin/Ability_Ultimate_End_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> deathmontage(TEXT("/Game/polytwin/Death_Fwd_Montage"));
	if (animmontage.Object)
	{
		Animmontage = animmontage.Object;
		//Animmontage = deathmontage.Object;
	}
	if (animmontage.Object)
	{
		AnimmontageDouble = animmontage.Object;
		//Animmontage = deathmontage.Object;
	}
	if (animmontageLeft.Object)
	{
		AnimmontageLeft = animmontageLeft.Object;
		//Animmontage = deathmontage.Object;
	}
	if (animmontageRight.Object)
	{
		AnimmontageRight = animmontageRight.Object;
		//Animmontage = deathmontage.Object;
	}
	if (deathmontage.Object)
	{
		Deathmontage = deathmontage.Object;
	}
	if (animmontageShotgun.Object)
	{
		AnimmontageShotgun = animmontageShotgun.Object;
	}
	if (animmontageCharge.Object)
	{
		AnimmontageCharge = animmontageCharge.Object;
	}
	if (animmontageChargeShot.Object)
	{
		AnimmontageChargeShot = animmontageChargeShot.Object;
	}
	if (animmontageChannel.Object)
	{
		AnimmontageChannel = animmontageChannel.Object;
	}
	if (animmontageChannelStart.Object)
	{
		AnimmontageChannelStart = animmontageChannelStart.Object;
	}
	if (animmontageChannelEnd.Object)
	{
		AnimmontageChannelEnd = animmontageChannelEnd.Object;
	}
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->bUsePawnControlRotation=true;
	CameraBoom->RelativeLocation = FVector(0, 0,120);

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	//Set Weapons Location
	const USkeletalMeshSocket* HandSocket;
	HandSocket = MeshComponent->GetSocketByName(TEXT("Hand_R"));
	FName handsocket = TEXT("Hand_R");
	//WeaponComponent->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepWorldTransform, handsocket);
	WeaponComponent->SetupAttachment(MeshComponent, handsocket);
	WeaponComponent->RelativeLocation=FVector(-8, -5, -5);
	//WeaponComponent->RelativeRotation = FRotator(180,110,-20);
	WeaponComponent->RelativeRotation = FRotator(180, 0, 0);
	FName leftsocket = TEXT("Hand_L");
	//LeftWeaponComponent->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepWorldTransform, leftsocket);
	LeftWeaponComponent->SetupAttachment(MeshComponent, leftsocket);
	LeftWeaponComponent->RelativeLocation = FVector(8, 5, 5);
	//LeftWeaponComponent->RelativeRotation = FRotator(0, -70, -20);
	LeftWeaponComponent->RelativeRotation = FRotator(0, 0, 0);
	GWeaponComponent->SetupAttachment(MeshComponent, handsocket);
	GWeaponComponent->RelativeLocation = FVector(-16, -14, -4);
	GWeaponComponent->RelativeRotation = FRotator(180, 20, 0);
	GWeaponComponent->RelativeScale3D=FVector(1.3, 1.3, 1.3);

	// Movement
	MoveSpeed = 900.0f;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	bUseControllerRotationYaw = false;
	skillsView = false;
	Hp = 100;
	MaxHp = 100;
	Exp = 0;
	Level = 1;
	Amo = 0;
	Reloadtime = 1;
	reloadPer = 0;
	faction = "User";

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	AttackRate = 0.7;
	AttackRateAmount = 1;
	AimComponent->SetupAttachment(CameraComponent);
	AimComponent->RelativeLocation = FVector(500, 0, 0);

	combonum = 0;

	if (shotsound.Object != nullptr)
		AttackSound = shotsound.Object;
	if (hitsound.Object != nullptr)
		HitSound = hitsound.Object;
	if (flamesound.Object != nullptr)
		FlameSound = flamesound.Object;
	if (chargesound.Object != nullptr)
		ChargeSound = chargesound.Object;
	if (chargeshotsound.Object != nullptr)
		ChargeShotSound = chargeshotsound.Object;
	if (shotgunsound.Object != nullptr)
		ShotGunSound = shotgunsound.Object;
	if (spreesound.Object != nullptr)
		SpreeSound = spreesound.Object;

	if (oasisbg.Object != nullptr)
		OasisBgm = oasisbg.Object;
	if (fairybg.Object != nullptr)
		FairyBgm = fairybg.Object;
	if (dampbg.Object != nullptr)
		DampBgm = dampbg.Object;
	if (tensionbg.Object != nullptr)
		TensionBgm= tensionbg.Object;

	if (chargeeffect.Object != nullptr)
		ChargeEffect = chargeeffect.Object;
	if (chargehiteffect.Object != nullptr)
		ChargeHitEffect = chargehiteffect.Object;
	if (channeleffect.Object != nullptr)
		ChannelEffect = channeleffect.Object;
	if (channelhiteffect.Object != nullptr)
		ChannelHitEffect = channelhiteffect.Object;

	BulletEffect = bulleteffect.Object;
	HitEffect = hiteffect.Object;
	SkillcoolAmount = 1;
	Spreeduration = 4;
	Spreecool = 10;
	Shotguncool = 6;
	Channelcool = 12;
	Chargecool = 8;
	spreePer = 0;
	shotgunPer = 0;
	chargePer = 0;
	channelPer = 0;
	skillPoint = 0;
	Dmg = 7;
	trigged = false;
	bCanSpree = false;
	Spreeing = false;
	bCanShotgun = false;
	bCanCharge = false;
	bCanChannel = false;
	channeling = false;
	charging = false;
	isReloading = false;
	MaxAmmo = 5;
	Ammo = MaxAmmo;

	StageBgm = OasisBgm;
	BossBgm = TensionBgm;

	for (int i = 0; i < 12; i++)
	{
		SkillLeveli.Add(0);
	}
}

void AUserChar::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis(LookForwardBinding);
	PlayerInputComponent->BindAxis(TurnRightBinding);

	PlayerInputComponent->BindAxis("MoveForward", this, &AUserChar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUserChar::MoveRight);

	PlayerInputComponent->BindAxis("Turn",this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRight", this, &AUserChar::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookForward", this, &AUserChar::LookUpAtRate);

	PlayerInputComponent->BindAction("Aim_pressed", IE_Pressed, this, &AUserChar::TriggerPressed);
	PlayerInputComponent->BindAction("Aim_released", IE_Released, this, &AUserChar::TriggerReleased);

	PlayerInputComponent->BindAction("Spree", IE_Released , this, &AUserChar::Spree);
	PlayerInputComponent->BindAction("Shotgun", IE_Released, this, &AUserChar::Shotgun);
	PlayerInputComponent->BindAction("Channel", IE_Released, this, &AUserChar::Channeling);
	PlayerInputComponent->BindAction("Charge", IE_Released, this, &AUserChar::Charge);
	
	PlayerInputComponent->BindAction("Reload", IE_Released, this, &AUserChar::Reloading);
}

// Called when the game starts or when spawned
void AUserChar::BeginPlay()
{
	Super::BeginPlay();
	FName handsocket = TEXT("Hand_R");
	FName leftsocket = TEXT("Hand_L");
	WeaponComponent->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepWorldTransform, handsocket);
	LeftWeaponComponent->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepWorldTransform, leftsocket);
	GWeaponComponent->SetVisibility(false);
	isboss = false;
	//UGameplayStatics::PlaySoundAtLocation(this, OasisBgm, GetActorLocation());
}
// Called every frame
void AUserChar::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// Find movement direction
	//HpbarRef = Cast<URogHpbar>(HpWidgetComp->GetUserWidgetObject());
	HpbarRef->SetHp(Hp);
	if (Hp > 0&&live)
	{
		const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
		const float RightValue = GetInputAxisValue(MoveRightBinding);

		// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
		const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

		// Calculate  movement
		const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;
		const FRotator TurnRotation = FRotator(0, GetControlRotation().Yaw, 0);
		// If non-zero size, move this actor
		//if (bCanFire == true)
		//{
		TRDebug = TurnRotation;
		FHitResult Hit(1.f);
		SetActorRotation(TurnRotation);
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			SetActorRotation(TurnRotation);
		}
		if (!channeling)
			Aim();
		else if (channeling)
		if (channeling)
			ChannelShot(RootComponent->GetForwardVector());
		if (Exp / 100 - Level >= 0)
		{
			LevelUp();
		}
	}
	else if (Hp <= 0)
	{
		Death();
		Hp--;
		InputEnabled();
	}
	
	// Create fire direction vector
	//const float FireForwardValue = GetInputAxisValue(LookForwardBinding);
	//const float FireRightValue = GetInputAxisValue(TurnRightBinding);
	//const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);

	// Try and fire a shot
	//Attack(FireDirection);
}

bool AUserChar::GetitemView()
{
	return skillsView;
}
void AUserChar::SetitemView(bool itemview)
{
	skillsView = itemview;
}
void AUserChar::LevelUp()
{
	Level += 1;
	MaxHp += 15;
	Hp += 15;
	skillsView =true;
	skillPoint++;
	//RandomPowerUps();
}
int AUserChar::GetSkillPoint()
{
	return skillPoint;
}
void AUserChar::SetSkillPoint(int point)
{
	skillPoint = point;
}
void AUserChar::Prox_Implementation(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bCanFire==false)
	{
		if (bCanDmg == true)
		{
			if (Cast<AEnemy>(OtherActor) == nullptr)
			{
				return;
			}
			AEnemy* target = Cast<AEnemy>(OtherActor);
			target->Hp -= 1;
			bCanDmg = false;
		}
	}
}
void AUserChar::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}
void AUserChar::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
void AUserChar::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AUserChar::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
void AUserChar::Aim()
{
	FHitResult hit;
	//FVector strace = GetActorLocation() + (GetActorForwardVector() * 60);
	//FVector etrace = strace + (GetActorForwardVector() * 1500);
	FVector strace = AimComponent->GetComponentLocation()  + (AimComponent->GetForwardVector() * 60);
	FVector etrace = strace + (AimComponent->GetForwardVector() * 3000);
	GetWorld()->LineTraceSingleByObjectType(hit, strace, etrace, ECollisionChannel::ECC_Pawn);
	if (!trigged)
		return;
	if (hit.GetActor() == nullptr&&!Spreeing)
	{
		return;
	}
	else if (Spreeing)
	{
		Combo(etrace);
	}
	else
	{
		if (Cast<AEnemy>(hit.GetActor()) == nullptr)
		{
			return;
		}
		AEnemy* target = Cast<AEnemy>(hit.GetActor());
		FVector Movement = target->GetActorLocation();
		if (bossinfo == false&&target->isBoss())
		{
			Target = target;
			bossinfo = true;
		}
		if (bCanDmg&&target->Hp>0&&Ammo>0)
			Combo(Movement);
	}
}
void AUserChar::Combo(FVector FireDirection)
{
	if (isReloading)
		ReloadCancel();
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, "!");
	SwapWeapons(GWeaponComponent, WeaponComponent);
	FVector gunoffset = FVector(0, 0, 0);
	FVector gunfireLo = FVector(0, 0, 0);
	//if (Spreeing && combonum < 2)
		//combonum = 2;
	switch (combonum)
	{
	case 0: Animmontage = AnimmontageRight; AttackRate = 0.6 * AttackRateAmount; gunfireLo = LeftWeaponComponent->GetComponentTransform().GetLocation(); break;
	case 1: Animmontage = AnimmontageLeft; AttackRate = 0.6 * AttackRateAmount; gunfireLo = WeaponComponent->GetComponentTransform().GetLocation(); break;
	//case 2: Animmontage = AnimmontageDouble; AttackRate = 0.15; gunfireLo = WeaponComponent->GetComponentTransform().GetLocation(); break;
	//case 3: Animmontage = AnimmontageDouble; AttackRate = 1.5 * AttackRateAmount; gunfireLo = LeftWeaponComponent->GetComponentTransform().GetLocation(); break;
	};
	gunoffset = gunfireLo - GetActorLocation();
	if (bCanFire)
	{
		if (combonum < 1)
			combonum++;
		else
			combonum = 0;
		//if (combonum == 0)
			//ExtraShot(FireDirection- gunfireLo, gunoffset);
		//else
			Attack(FireDirection- gunfireLo, gunoffset);
		if (combonum>0&&combonum<2)
		{
			UWorld* const World = GetWorld();
			World->GetTimerManager().SetTimer(TimerHandle_ComboTimerExpired, this, &AUserChar::ComboReset, AttackRate*1.5);
		}
		Ammo -= 1;
	}
	if (Ammo <= 0&&!isReloading)
		Reloading();
}
void AUserChar::ComboReset()
{
	if (bCanFire)
	{
		combonum = 0;
	}
}
void AUserChar::ExtraShot(FVector FireDirection, FVector gunoffset)
{
	if (bCanFire == true)
	{
		if (FireDirection.SizeSquared() > 0.0f)
		{

			UWorld* const World = GetWorld();
			const FRotator FireRotation = FireDirection.Rotation();
			const FVector SpawnLocation = GetActorLocation(); 
			if (World != NULL)
			{
				ABullet* bullet;
				// spawn the projectile
				bullet = World->SpawnActor<ABullet>(SpawnLocation + gunoffset, FireRotation);
				bullet->Shooter = this;
				bullet->SetDmg(Dmg);
				if (BulletEffect != nullptr)
				{
					bullet->SetParticle(BulletEffect);
				}
				if (HitEffect != nullptr)
				{
					bullet->SetHitParticle(HitEffect);
				}
				if (AttackSound != nullptr)
				{
					UGameplayStatics::PlaySoundAtLocation(this, AttackSound, GetActorLocation());
				}
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ARogCharacter::AttackTimerExpired, AttackRate);
			SetActorRotation(FireRotation);
		}
		Ammo -= 1;
	}
}
void AUserChar::TriggerPressed()
{
	trigged = true;
}
void AUserChar::TriggerReleased()
{
	trigged = false;
	Reloading();
}
void AUserChar::SetUIHp()
{
}
void AUserChar::Spree()
{
	if (bCanSpree&&!isSkillCast)
	{
		Spreeing = true;
		UGameplayStatics::PlaySoundAtLocation(this, SpreeSound, GetActorLocation());
		UWorld* const World = GetWorld();
		World->GetTimerManager().SetTimer(TimerHandle_SpreeTimerExpired, this, &AUserChar::SpreeCool, Spreecool*SkillcoolAmount);
		World->GetTimerManager().SetTimer(TimerHandle_SpreeDurationTimerExpired, this, &AUserChar::SpreeDuration, Spreeduration+SkillLeveli[0]);
		spreePer = Spreecool * SkillcoolAmount;
		World->GetTimerManager().SetTimer(TimerHandle_SpreeCoolExpired, this, &AUserChar::SpreePer, 0.033,true);
		bCanSpree = false;
		AttackRateAmount = 0.9*4/(SkillLeveli[0]+4);
	}
}
void AUserChar::SpreeCool()
{
	UWorld* const World = GetWorld();
	World->GetTimerManager().ClearTimer(TimerHandle_SpreeCoolExpired);
	spreePer = 0;
	bCanSpree = true;
}
void AUserChar::SpreeDuration()
{
	Spreeing = false;
	AttackRateAmount = 1;
}
void AUserChar::Shotgun()
{
	if (bCanShotgun&& !isSkillCast)
	{
		bCanFire = false;
		bCanShotgun = false;
		SwapWeapons(WeaponComponent, GWeaponComponent);
		PlayAnimMontage(AnimmontageShotgun, 1);
		UGameplayStatics::PlaySoundAtLocation(this, ShotGunSound, GetActorLocation());

		UWorld* const World = GetWorld();

		FVector Movement = RootComponent->GetForwardVector();
		FVector gunoffset = FVector(150, 0, 0);
		if (ChargeBullet != nullptr)
			ChargeBullet->EndEffect();
		if (World != NULL)
		{
			UWorld* const World = GetWorld();
			const FRotator FireRotation = Movement.Rotation();
			const FVector SpawnLocation = GetActorLocation();
			ARogExplosionActor* effect;
			float shotlo = (SkillLeveli[1] + 2)/2*3;
			for (int i = 0; i < SkillLeveli[1] + 2; i++)
			{
				ABullet* bullet;
				FRotator shotRo = FireRotation + FRotator( 0, -shotlo+(i*3),0);
				bullet = World->SpawnActor<ABullet>(SpawnLocation + FVector(0, 50, 40), shotRo);
				bullet->Shooter = this;
				bullet->SetDmg(Dmg + ((Dmg / 4) * SkillLeveli[1]));
				if (BulletEffect != nullptr)
					bullet->SetParticle(BulletEffect);
				if (HitEffect != nullptr)
					bullet->SetHitParticle(HitEffect);
				if (AttackSound != nullptr)
					UGameplayStatics::PlaySoundAtLocation(this, AttackSound, GetActorLocation());
			}
			// spawn the projectile
			effect = World->SpawnActor<ARogExplosionActor>(SpawnLocation + FireRotation.RotateVector(gunoffset), FireRotation);
			effect->Shooter = this;
			effect->SetDmg(Dmg + ((Dmg / 4) * SkillLeveli[1]));
			if (ChargeEffect != nullptr)
				effect->SetParticle(ChargeHitEffect);
			if (ChargeHitEffect != nullptr)
				effect->SetHitParticle(ChargeHitEffect);
		}

		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ARogCharacter::AttackTimerExpired, 1.5);
		World->GetTimerManager().SetTimer(TimerHandle_ShotgunTimerExpired, this, &AUserChar::ShotgunCool, Shotguncool*SkillcoolAmount);
		shotgunPer = Shotguncool * SkillcoolAmount;
		World->GetTimerManager().SetTimer(TimerHandle_ShotgunCoolExpired, this, &AUserChar::ShotgunPer, 0.033, true);
	}
}
void AUserChar::ShotgunCool()
{
	UWorld* const World = GetWorld();
	World->GetTimerManager().ClearTimer(TimerHandle_ShotgunCoolExpired);
	shotgunPer = 0;
	bCanShotgun = true;
}
void AUserChar::Channeling()
{
	if (bCanChannel&& !isSkillCast)
	{
		bCanChannel = false;
		bCanDmg = false;
		isSkillCast = true;
		PlayAnimMontage(AnimmontageChannelStart, 1);
		UWorld* const World = GetWorld();
		World->GetTimerManager().SetTimer(TimerHandle_ChannelingTimerExpired, this, &AUserChar::ChannelingOff, 3);
		World->GetTimerManager().SetTimer(TimerHandle_ChannelTimerExpired, this, &AUserChar::ChannelingCool, Channelcool*SkillcoolAmount);
		channelPer = Channelcool * SkillcoolAmount;
		World->GetTimerManager().SetTimer(TimerHandle_ChannelCoolExpired, this, &AUserChar::ChannelPer, 0.033, true);
	}
}
void AUserChar::ChannelingOff()
{
	PlayAnimMontage(AnimmontageChannelEnd, 1);
	channeling = false;
	isSkillCast = false;
	UWorld* const World = GetWorld();
	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ARogCharacter::AttackTimerExpired, 0.8);
}
void AUserChar::ChannelingCool()
{
	UWorld* const World = GetWorld();
	World->GetTimerManager().ClearTimer(TimerHandle_ChannelCoolExpired);
	channelPer = 0;
	bCanChannel = true;
}
void AUserChar::ChannelShot(FVector FireDirection)
{
	if (channeling)
	{
		if (FireDirection.SizeSquared() > 0.0f)
		{
			FVector gunoffset = FVector(20, 0, 0);
			UWorld* const World = GetWorld();
			const FRotator FireRotation = FireDirection.Rotation();
			const FVector SpawnLocation = GetActorLocation();
			//PlayAnimMontage(AnimmontageChannel, 1);
			if (World != NULL)
			{
				ABullet* bullet;
				// spawn the projectile
				bullet = World->SpawnActor<ABullet>(SpawnLocation + FireRotation.RotateVector(gunoffset), FireRotation);
				bullet->Shooter = this;
				bullet->SetDmg(SkillLeveli[2]*(Dmg/4));
				bullet->SetLifeSpan(1.0f);
				if (ChannelEffect != nullptr)
				{
					bullet->SetParticle(ChannelEffect);
				}
				if (ChannelHitEffect != nullptr)
				{
					bullet->SetHitParticle(ChannelHitEffect);
				}
			}
			SetActorRotation(FireRotation);
		}
	}
}
void AUserChar::ChannelingStart_Implementation()
{
	channeling = true;
	if (AttackSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FlameSound, GetActorLocation(),2.5,2);
	}
}
void AUserChar::Charge()
{
	if (bCanCharge && !isSkillCast)
	{
		charging = true;
		isSkillCast = true;
		PlayAnimMontage(AnimmontageCharge, 1);
		UGameplayStatics::PlaySoundAtLocation(this, ChargeSound, GetActorLocation(),2,2);
		UWorld* const World = GetWorld();
		World->GetTimerManager().SetTimer(TimerHandle_ChargeTimerExpired, this, &AUserChar::ChargeCool, Chargecool * SkillcoolAmount);
		World->GetTimerManager().SetTimer(TimerHandle_ChargingTimerExpired, this, &AUserChar::ChargeShot, 0.8);
		chargePer = Chargecool * SkillcoolAmount;
		World->GetTimerManager().SetTimer(TimerHandle_ChargeCoolExpired, this, &AUserChar::ChargePer, 0.033, true);
		bCanCharge = false;
		bCanFire = false;
		FVector Movement = FVector(0, 0, 0);
		Movement = Target->GetActorLocation() - GetActorLocation();
		FVector gunoffset = FVector(0, 0, 300);
		SwapWeapons(WeaponComponent, GWeaponComponent);
		/*if (World != NULL)
		{
			UWorld* const World = GetWorld();
			const FRotator FireRotation = Movement.Rotation();
			const FVector SpawnLocation = GetActorLocation();
			ARogEffect* effect;
			// spawn the projectile
			effect = World->SpawnActor<ARogEffect>(SpawnLocation + FireRotation.RotateVector(gunoffset), FireRotation);
			if (ChargeEffect != nullptr)
				effect->SetParticle(ChargeEffect);
			//if (ChargeSound != nullptr)
				//UGameplayStatics::PlaySoundAtLocation(this, ChargeSound, GetActorLocation(), 0.7f);
			ChargeBullet = effect;
		}*/
	}
}
void AUserChar::ChargeShot()
{
	charging = false;
	isSkillCast = false;
	FVector Movement = RootComponent->GetForwardVector();
	FVector gunoffset = FVector(40, 0, 0);
	//PlayAnimMontage(AnimmontageChargeShot, 1);
	UWorld* const World = GetWorld();
	UGameplayStatics::PlaySoundAtLocation(this, ChargeShotSound, GetActorLocation());
	if (ChargeBullet != nullptr)
		ChargeBullet->EndEffect();
	if (World != NULL)
	{
		UWorld* const World = GetWorld();
		const FRotator FireRotation = Movement.Rotation();
		const FVector SpawnLocation = GetActorLocation();
		ABullet* effect;
		// spawn the projectile
		effect = World->SpawnActor<ABullet>(SpawnLocation + FireRotation.RotateVector(gunoffset), FireRotation);
		effect->SetActorScale3D(FVector(2,2,2));
		effect->Shooter = this;
		effect->SetDmg(Dmg* (SkillLeveli[3]+1));
		if (ChargeEffect != nullptr)
			effect->SetParticle(ChargeEffect);
		if (ChargeHitEffect != nullptr)
			effect->SetHitParticle(ChargeHitEffect);
	}
	SetActorRotation(Movement.Rotation());
	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ARogCharacter::AttackTimerExpired, 0.8);
}
void AUserChar::ChargeCool()
{
	UWorld* const World = GetWorld();
	bCanCharge = true;
	World->GetTimerManager().ClearTimer(TimerHandle_ChargeCoolExpired);
	chargePer = 0;
}

void AUserChar::Reload()
{
	isReloading = false;
	reloadPer = 0;
	UWorld* const World = GetWorld();
	World->GetTimerManager().ClearTimer(TimerHandle_ReloadRateExpired);
	Ammo = MaxAmmo;
}

void AUserChar::Reloading()
{
	UWorld* const World = GetWorld();
	//reloadPer = Reloadtime;
	isReloading = true;
	World->GetTimerManager().SetTimer(TimerHandle_ReloadRateExpired, this, &AUserChar::ReloadPer, 0.033, true);
	World->GetTimerManager().SetTimer(TimerHandle_ReloadExpired, this, &AUserChar::Reload, Reloadtime);
}
void AUserChar::ReloadCancel()
{
	isReloading = false;
	reloadPer = 0;
	UWorld* const World = GetWorld();
	World->GetTimerManager().ClearTimer(TimerHandle_ReloadRateExpired);
	World->GetTimerManager().ClearTimer(TimerHandle_ReloadExpired);
}
void AUserChar::SwapWeapons(USkeletalMeshComponent* weapon, USkeletalMeshComponent* toweapon)
{
	if (weapon == WeaponComponent)
	{
		LeftWeaponComponent->SetVisibility(false);
	}
	if (toweapon == WeaponComponent)
	{
		LeftWeaponComponent->SetVisibility(true);
	}
	weapon->SetVisibility(false);
	toweapon->SetVisibility(true);
}

void AUserChar::SpreePer()
{
	spreePer-=0.033;
	if (spreePer < 0)
		spreePer = 0;

}
void AUserChar::ShotgunPer()
{
	shotgunPer -= 0.033;
	if (shotgunPer < 0)
		shotgunPer = 0;
}
void AUserChar::ChannelPer()
{
	channelPer -= 0.033;
	if (channelPer < 0)
		channelPer = 0;
}
void AUserChar::ChargePer()
{
	chargePer -= 0.033;
	if (chargePer < 0)
		chargePer = 0;
}
void AUserChar::ReloadPer()
{
	reloadPer += 0.033;
	if (reloadPer > Reloadtime)
		reloadPer = 0;
}
float AUserChar::GetSkillCooldown(int skill)
{
	switch (skill)
	{
	case 0:return spreePer/(Spreecool * SkillcoolAmount); break;
	case 1:return shotgunPer/(Shotguncool * SkillcoolAmount); break;
	case 2:return channelPer/(Channelcool * SkillcoolAmount);  break;
	case 3:return chargePer/(Chargecool * SkillcoolAmount);  break;
	}
	return 0;
}
void AUserChar::SkillLevelUp(int Skillnum)
{
	/*
	* 0 = spree;
	* 1 = shotgun;
	* 2 = channel;
	* 3 = charge;
	* 4 = dmg;
	* 5 = armor;
	* 6 = crit;
	* 7 = critdmg;
	* 8 = Hp;
	* 9 = cool;
	* 10 = speed;
	*/
	SkillLeveli[Skillnum] += 1;
	switch (Skillnum)
	{
	case 4: Dmg += 2; break;
	case 5: Armor += 1; break;
	case 6: Crit += 1; break;
	case 7: CritDmg += 0.3; break;
	case 8: Hp += 10; MaxHp += 10; break;
	case 9:  CooldownRate -= 0.05; break;
	case 10: MoveSpeed += 5; break;
	case 11: MaxAmmo += 1; break;
	default: break;
	}
}
int AUserChar::GetSkillLevel(int Skillnum)
{
	return SkillLeveli[Skillnum];
}
void AUserChar::BCanSkill(int Skillnum)
{
	switch (Skillnum)
	{
	case 0: bCanSpree = true; break;
	case 1: bCanShotgun =true; break;
	case 2: bCanChannel = true; break;
	case 3: bCanCharge = true; break;
	default: break;
	}
}
int AUserChar::GetAmmo()
{
	return Ammo;
}
int AUserChar::GetMaxAmmo()
{
	return MaxAmmo;
}
float AUserChar::GetReloadRate()
{
	return reloadPer/Reloadtime;
}
void AUserChar::SetLevelCount(int lc)
{
	Super::SetLevelCount(lc);
	StageBgm = FairyBgm;
}
// Called to bind functionality to input

