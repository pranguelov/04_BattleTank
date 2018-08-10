// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"


//Tick
	//Super
	//AimTowardsCrosshair()




void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController::BeginPlay %s"), *(GetControlledTank()->GetName()));
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	FVector hitLocation; //out param
	if (GetSightRayHitLocation(hitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation %s"), *(hitLocation.ToString()));
		//if it hits the landscape
			//tell controlled tank to aim at this point
	}
}

//Get world location if linetrace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
	//Find crosshair position in screen coords
	int32 viewPortSizeX, viewPortSizeY;
	GetViewportSize(viewPortSizeX, viewPortSizeY);
	auto screenLocation = FVector2D(CrossHairXLocation * viewPortSizeX, CrossHairYLocation * viewPortSizeY);

	//"De-project" screen pos to a world direction
	FVector lookDirection;
	if (GetLookDirection(screenLocation, lookDirection))
	{
		//Line trace along that direction and see what we hit
		if (GetLookVectorHitLocation(lookDirection, hitLocation))
		{
			return true;
		}
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(const FVector2D& screenLocation, FVector& lookDirection) const
{
	FVector cameraWorldLocation;
	bool result =  DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);
	//UE_LOG(LogTemp, Warning, TEXT("DeprojectScreenPositionToWorld Camera %s  "), *(cameraWorldLocation.ToString()));
	return result;

}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& lookDirection, FVector& hitLocation) const
{
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	//UE_LOG(LogTemp, Warning, TEXT("GetLookVectorHitLocation Camera %s  "), *(startLocation.ToString()));

	auto endLocation = startLocation + lookDirection * LineTraceRange;
	if( GetWorld()->LineTraceSingleByChannel(
			hitResult,
			startLocation,
			endLocation,
			ECollisionChannel::ECC_Visibility)
	)
	{
		hitLocation = hitResult.Location;
		return true;
	}
	hitLocation = FVector(0);
	return false;
	
}