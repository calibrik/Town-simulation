// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpeedrunShooterCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ShooterHUD.h"
#include "Weapon/Weapon.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ASpeedrunShooterCharacter

ASpeedrunShooterCharacter::ASpeedrunShooterCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	MaxHealth=100;
	CurrHealth=MaxHealth;
	OldHealth=CurrHealth;
}

void ASpeedrunShooterCharacter::Regen(float Value)
{
	SetHealth(FMath::Lerp(OldHealth,MaxHealth,Value));
}

void ASpeedrunShooterCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	HUD=Cast<AShooterHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD());
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	HUD->SetHealthBarPercent(1);
	FOnTimelineFloat TimelineFloat;
	TimelineFloat.BindUFunction(this,FName("Regen"));
	RegenTimeline.AddInterpFloat(RegenRateCurve,TimelineFloat);
	FActorSpawnParameters WeaponSpawnParams;
	WeaponSpawnParams.Owner=this;
	Weapon=GetWorld()->SpawnActor<AWeapon>(WeaponClass,FVector::Zero(),FRotator::ZeroRotator,WeaponSpawnParams);
	Weapon->Setup(this);
}

void ASpeedrunShooterCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	RegenTimeline.TickTimeline(DeltaSeconds);
}

//////////////////////////////////////////////////////////////////////////// Input

void ASpeedrunShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASpeedrunShooterCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASpeedrunShooterCharacter::Look);
		
		EnhancedInputComponent->BindAction(ToggleWeaponAction,ETriggerEvent::Triggered,this,&ASpeedrunShooterCharacter::ToggleWeapon);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ASpeedrunShooterCharacter::LaunchCharacter(FVector LaunchVelocity, bool bXYOverride, bool bZOverride)
{
	if (GetVelocity().Z<0&&LaunchVelocity.Z>0)
		LaunchVelocity=FVector(LaunchVelocity.X,LaunchVelocity.Y,LaunchVelocity.Z*2);
	Super::LaunchCharacter(LaunchVelocity, bXYOverride, bZOverride);
}

void ASpeedrunShooterCharacter::Damage(float Damage)
{
	if (RegenTimeline.IsPlaying())
		RegenTimeline.Stop();
	GetWorldTimerManager().ClearTimer(RegenWaitHandle);
	SetHealth(CurrHealth-Damage);
	OldHealth=CurrHealth;
	GetWorldTimerManager().SetTimer(RegenWaitHandle,[this]()
	{
		RegenTimeline.SetPlaybackPosition(CurrHealth/MaxHealth,true);
		RegenTimeline.Play();
	},RegenWaitTime,false);
}

void ASpeedrunShooterCharacter::SetHealth(float NewHealth)
{
	CurrHealth=FMath::Clamp(NewHealth,0,MaxHealth);
	HUD->SetHealthBarPercent(CurrHealth/MaxHealth);
}


void ASpeedrunShooterCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ASpeedrunShooterCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASpeedrunShooterCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ASpeedrunShooterCharacter::GetHasRifle()
{
	return bHasRifle;
}

void ASpeedrunShooterCharacter::ToggleWeapon()
{
	if (!Weapon)
		return;
	GetHasRifle()?Weapon->HideWeapon():Weapon->ShowWeapon();
}

bool ASpeedrunShooterCharacter::IsActorBeingSeenByPlayer(const AActor* Actor) const
{
	FVector TraceStart{Actor->GetActorLocation()};
	TraceStart+=FVector(0,0,100);//bruh
	FVector TraceEnd{FirstPersonCameraComponent->GetComponentLocation()};
	// FVector TraceEnd{GetActorLocation()};
	// UE_LOG(LogTemp,Log,TEXT("%f %f"),FVector::DotProduct((TraceStart-TraceEnd).GetSafeNormal(),GetActorForwardVector()),FMath::Cos(90*PI/180));
	if (FVector::DotProduct((TraceStart-TraceEnd).GetSafeNormal(),GetActorForwardVector())<FMath::Cos(55*PI/180))
		return false;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Actor);
	FHitResult ResultHit;
	if (GetWorld()->LineTraceSingleByChannel(ResultHit,TraceStart,TraceEnd,ECC_Camera,QueryParams))
	{
		if (ResultHit.GetActor()==this)
			return true;
	}
	return false;
}
