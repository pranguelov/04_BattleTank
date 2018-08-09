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
	//Find crosshair position
	int32 viewPortSizeX, viewPortSizeY;
	GetViewportSize(viewPortSizeX, viewPortSizeY);
	auto ScreenLocation = FVector2D(CrossHairXLocation * viewPortSizeX, CrossHairYLocation * viewPortSizeY);
	
	UE_LOG(LogTemp, Warning, TEXT("ScreenLocation %s"), *(ScreenLocation.ToString()));

	//"De-project" screen pos to a world direction
	//Line trace along that direction and see what we hit
	return false;
}