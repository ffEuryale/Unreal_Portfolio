// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderMovementComponent.h"

void UColliderMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) return;

	FVector DesiredMoventThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.f);

	if (!DesiredMoventThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMoventThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		//만약 어떤 물체에 부딫혔을 경우 옆으로 미끄러지게
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMoventThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);

			UE_LOG(LogTemp, Warning, TEXT("Valid Blocking Hit"));
		}
	}

}










