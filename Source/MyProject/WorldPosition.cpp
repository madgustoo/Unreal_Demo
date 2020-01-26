// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();

	FString ObjectPosition = GetOwner()->GetActorTransform().GetLocation().ToString();

	// UE_LOG is expecting a TCHAR array, and the * effectively converts the string to this type.
	// * OPERATOR if you place a string: %s
	// For example, %f doesn't require 
	UE_LOG(LogTemp, Warning, TEXT("Object name: %s"), *ObjectName);
	UE_LOG(LogTemp, Warning, TEXT("Object position: %s"), *ObjectPosition);
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

