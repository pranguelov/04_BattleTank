// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


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

	//deproject to get world
	FVector lookDirection;
	if( GetLookDirection(screenLocation, lookDirection) )
	{
		UE_LOG(LogTemp, Warning, TEXT("ScreenLocation %s  WorldLocation %s"), *(screenLocation.ToString()), *(lookDirection.ToString()));
	}

	//"De-project" screen pos to a world direction
	//Line trace along that direction and see what we hit
	return false;
}

bool ATankPlayerController::GetLookDirection(const FVector2D& screenLocation, FVector& lookDirection) const
{
	FVector cameraWorldLocation;
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);


}