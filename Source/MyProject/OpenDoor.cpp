// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw; // TargetYaw = InitialYaw + 90.f;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has the open door component, but no pressureplate attached!"), *GetOwner()->GetName());
	}

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if PressurePlate not null
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens)) 
	{
		OpenDoor(DeltaTime);
	} else {
		CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime) 
{
	// Linear interpolation (LERP) involves estimating a new value by connecting two adjacent known values with a straight line
	// Point de debart -> Point d'arriver : estimer les points entre les deux 
	// DeltaTime * 1.f is the speed 
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * 0.5f);

	/** Yaw is rotation around the up axis (around Z axis), Running in circles 0=East, +North, -South. */
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * 1.f);

	/** Yaw is rotation around the up axis (around Z axis), Running in circles 0=East, +North, -South. */
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

