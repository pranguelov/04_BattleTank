// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"



ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	ATank* playerTank = nullptr;
	playerTank = Cast<ATank>( GetWorld()->GetFirstPlayerController()->GetPawn() );	

	return playerTank;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ATankAIController::BeginPlay. Controlled Tank %s"), *(GetControlledTank()->GetName()));

	UE_LOG(LogTemp, Warning, TEXT("ATankAIController::BeginPlay Player Tank %s"), *(GetPlayerTank()->GetName()));
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto playerTank = GetPlayerTank();
	auto ourTank = GetControlledTank();
	if (playerTank && ourTank)
	{
		//TODO Movetowards the player

		ourTank->AimAt(playerTank->GetActorLocation());
	}
}