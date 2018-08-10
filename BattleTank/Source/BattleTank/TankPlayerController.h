// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	

private:
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.34;

	ATank * GetControlledTank() const;
	

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	//Start the tank moving the barrel so
	//that a shot would hit there the crosshairs 
	//intersect the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& hitLocation) const;	

	bool GetLookDirection(const FVector2D& screenLocation, FVector& lookDirection) const;
	
};
