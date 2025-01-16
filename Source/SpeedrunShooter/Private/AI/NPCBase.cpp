// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NPCBase.h"

#include "SpeedrunShooterCharacter.h"
#include "Actors/PatrolRoute.h"
#include "AI/NPCBaseAIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HealthBarWidget.h"

void ANPCBase::UnFreeze(UAnimMontage* Montage, bool bInterrupted)
{
	
}

void ANPCBase::ToggleHealthBar()
{
	if (Health==MaxHealth||!IsAlive()||!Player->IsActorBeingSeenByPlayer(this))
	{
		if (bIsHealthBarVisible)
		{
			bIsHealthBarVisible=false;
			HealthBarWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
		return;
	}
	if (!bIsHealthBarVisible)
	{
		bIsHealthBarVisible=true;
		HealthBarWidget->SetVisibility(ESlateVisibility::Visible);
	}
	// FVector TraceStart{GetActorLocation()};
	// TraceStart+=FVector(0,0,100);
	// FVector TraceEnd{Player->GetActorLocation()};
	// // UE_LOG(LogTemp,Log,TEXT("%f %f"),FVector::DotProduct((TraceStart-TraceEnd).GetSafeNormal(),Player->GetActorForwardVector()),FMath::Cos(30.0f*PI/180));
	// if (FVector::DotProduct((TraceStart-TraceEnd).GetSafeNormal(),Player->GetActorForwardVector())<FMath::Cos(55.0f*PI/180))
	// {
	// 	if (bIsHealthBarVisible)
	// 	{
	// 		bIsHealthBarVisible=false;
	// 		HealthBarWidget->SetVisibility(ESlateVisibility::Collapsed);
	// 	}
	// 	return;
	// }
	// FCollisionQueryParams QueryParams;
	// QueryParams.AddIgnoredActor(this);
	// FHitResult ResultHit;
	// if (GetWorld()->LineTraceSingleByChannel(ResultHit,TraceStart,TraceEnd,ECC_Camera,QueryParams))
	// {
	// 	if (ResultHit.GetActor()==Player)
	// 	{
	// 		if (!bIsHealthBarVisible)
	// 		{
	// 			bIsHealthBarVisible=true;
	// 			HealthBarWidget->SetVisibility(ESlateVisibility::Visible);
	// 		}
	// 	}
	// 	else
	// 	{
	// 		if (bIsHealthBarVisible)
	// 		{
	// 			bIsHealthBarVisible=false;
	// 			HealthBarWidget->SetVisibility(ESlateVisibility::Collapsed);
	// 		}
	// 	}
	// }
}

void ANPCBase::Freeze()
{
	AIController->SetState(Frozen);
	if (AnimInstance&&HitAnim)
		GetMesh()->GetAnimInstance()->Montage_Play(HitAnim);
	else
		UnFreeze(nullptr,false);
}

void ANPCBase::IncrementPatrolRouteIndex()
{
	PatrolRouteDirection?PatrolRouteIndex+=1:PatrolRouteIndex-=1;
	uint8 Total=PatrolRoute->GetTotal();
	if (PatrolRouteIndex==Total)
		PatrolRouteIndex=0;
	if (PatrolRouteIndex<0)
		PatrolRouteIndex=Total-1;
}

// Sets default values
ANPCBase::ANPCBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MaxHealth=100;
	PatrolRouteIndex=-10;
	Health=MaxHealth;
	HealthBarComponent=CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"));
	// HealthBarComponent->AttachToComponent(GetMesh(),FAttachmentTransformRules(EAttachmentRule::SnapToTarget,false));
	HealthBarComponent->SetupAttachment(GetMesh());
	bIsHealthBarVisible=false;
	PatrolRouteDirection=true;
}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
	if (HealthBarComponent->GetWidgetClass())
	{
		HealthBarWidget=CreateWidget<UHealthBarWidget>(GetWorld(),HealthBarComponent->GetWidgetClass());
		HealthBarComponent->SetWidget(HealthBarWidget);
		HealthBarWidget->SetHealthBarPercent(1);
	}
	AIController=Cast<ANPCBaseAIController>(GetController());
	AnimInstance=GetMesh()->GetAnimInstance();
	if (AnimInstance)
		AnimInstance->OnMontageEnded.AddDynamic(this,&ANPCBase::UnFreeze);
	HealthBarWidget->SetVisibility(ESlateVisibility::Collapsed);
	Player=Cast<ASpeedrunShooterCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	GetWorldTimerManager().SetTimer(HealthBarVisionHandle,this,&ANPCBase::ToggleHealthBar,0.1,true);
	if (!PatrolRoute)
	{
		PatrolRoute=Cast<APatrolRoute>(UGameplayStatics::GetActorOfClass(GetWorld(),APatrolRoute::StaticClass()));
	}
	AIController->SetState(Patroling,false);
}

// Called every frame
void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPCBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (!PropertyChangedEvent.Property) return;
	FName PropertyName=PropertyChangedEvent.Property->GetFName();
	if (PropertyName==GET_MEMBER_NAME_CHECKED(ANPCBase, MaxHealth))
		Health=MaxHealth;
}

void ANPCBase::Damage(float Damage)
{
	if (!IsAlive()) return;
	if (Health==MaxHealth)
		HealthBarWidget->SetVisibility(ESlateVisibility::Visible);
	Health=FMath::Clamp(Health-Damage,0,MaxHealth);
	HealthBarWidget->SetHealthBarPercent(Health/MaxHealth);
	Freeze();
	if (Health==0)
	{
		Die();
	}
}

void ANPCBase::Die()
{
	HealthBarWidget->SetVisibility(ESlateVisibility::Collapsed);
	GetMesh()->SetSimulatePhysics(true);
	// GetCapsuleComponent()->Deactivate();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	AIController->StopAI();
}

void ANPCBase::JumpTo(FVector Dest)
{
	// AIController->StopMovement();
	FVector Velocity;
	if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(GetWorld(),Velocity,GetActorLocation(),FVector(Dest.X,Dest.Y,Dest.Z+250),0,0.5))
		LaunchCharacter(Velocity,true,true);
}
