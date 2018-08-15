// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "Engine/World.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet)
{
	Barrel = barrelToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (!Barrel) { return; }


	FVector outLaunchVelocity;
	FVector startLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		outLaunchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		false,
		5.f,//float CollisionRadius,
		0.f, //float OverrideGravityZ,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray < AActor * >(),
		true //bool bDrawDebug
		)
	)
	{
		auto aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelToward(aimDirection);

		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aiming solution found "), time);		
	}
	else
	{
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No aiming solution "), time);
	}
}

void UTankAimingComponent::MoveBarrelToward(FVector aimDirection)
{
	//work-out difference between barrel and aim direction
	auto barrelRotator = Barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("Aiming rotator %s "), *(aimAsRotator.ToString()));

	Barrel->Elevate(5);

	

	//get aimDirection in Tank CS
	//extract Yaw and el
	//set those as new targets for turret and barrel
	//rotate barrel in tick 

}