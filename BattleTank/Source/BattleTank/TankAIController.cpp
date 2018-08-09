// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Engine/World.h"



ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	ATank* playerTank = nullptr;
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (playerController)
	{
		ATankPlayerController* tankPlayerController = Cast<ATankPlayerController>(playerController);
		if (tankPlayerController)
		{
			playerTank = tankPlayerController->GetControlledTank();
		}

	}

	return playerTank;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ATankAIController::BeginPlay. Controlled Tank %s"), *(GetControlledTank()->GetName()));

	UE_LOG(LogTemp, Warning, TEXT("ATankAIController::BeginPlay Player Tank %s"), *(GetPlayerTank()->GetName()));
}