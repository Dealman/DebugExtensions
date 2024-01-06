// Copyright 2023 'Dealman' - All Rights Reserved

#include "ExtendedDebugHelpers.h"
#include "KismetTraceUtils.h"
#include "PhysicsEngine/PhysicsSettings.h"


FCollisionQueryParams UExtendedDebugHelpers::ConfigureCollisionParamsEx(FName TraceTag, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, bool bIgnoreSelf, const UObject* WorldContextObject)
{
	FCollisionQueryParams Params(TraceTag, SCENE_QUERY_STAT_ONLY(KismetTraceUtils), bTraceComplex);
	Params.bReturnPhysicalMaterial = true;
	Params.bReturnFaceIndex = !UPhysicsSettings::Get()->bSuppressFaceRemapTable; // Ask for face index, as long as we didn't disable globally
	Params.AddIgnoredActors(ActorsToIgnore);
	if (bIgnoreSelf)
	{
		if (const AActor* IgnoreActor = Cast<AActor>(WorldContextObject))
		{
			Params.AddIgnoredActor(IgnoreActor);
		}
		else
		{
			// Find owner
			const UObject* CurrentObject = WorldContextObject;
			while (CurrentObject)
			{
				CurrentObject = CurrentObject->GetOuter();
				IgnoreActor = Cast<AActor>(CurrentObject);
				if (IgnoreActor)
				{
					Params.AddIgnoredActor(IgnoreActor);
					break;
				}
			}
		}
	}

	return Params;
}

FCollisionObjectQueryParams UExtendedDebugHelpers::ConfigureCollisionObjectParamsEx(const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes)
{
	TArray<TEnumAsByte<ECollisionChannel>> CollisionObjectTraces;
	CollisionObjectTraces.AddUninitialized(ObjectTypes.Num());

	for (auto Iter = ObjectTypes.CreateConstIterator(); Iter; ++Iter)
	{
		CollisionObjectTraces[Iter.GetIndex()] = UEngineTypes::ConvertToCollisionChannel(*Iter);
	}

	FCollisionObjectQueryParams ObjectParams;
	for (auto Iter = CollisionObjectTraces.CreateConstIterator(); Iter; ++Iter)
	{
		const ECollisionChannel & Channel = (*Iter);
		if (FCollisionObjectQueryParams::IsValidObjectQuery(Channel))
		{
			ObjectParams.AddObjectTypesToQuery(Channel);
		}
		else
		{
			UE_LOG(LogBlueprintUserMessages, Warning, TEXT("%d isn't valid object type"), (int32)Channel);
		}
	}

	return ObjectParams;
}

void UExtendedDebugHelpers::DrawDebugLineTraceSingleEx(const UWorld* World, const FVector& Start, const FVector& End, EDrawDebugTrace::Type DrawDebugType, ESceneDepthPriority DepthPriority, bool bHit, const FHitResult& HitResult, FLinearColor TraceColor, FLinearColor TraceHitColor, float Thickness, float PointSize, float DrawTime)
{
	if (DrawDebugType != EDrawDebugTrace::None)
	{
		const bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
		const float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

		if (bHit && HitResult.bBlockingHit)
		{
			DrawDebugLine(World, Start, HitResult.ImpactPoint, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority, Thickness);
			DrawDebugLine(World, HitResult.ImpactPoint, End, TraceHitColor.ToFColor(true), bPersistent, LifeTime, DepthPriority, Thickness);
			DrawDebugPoint(World, HitResult.ImpactPoint, PointSize, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
		}
		else
		{
			DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority, Thickness);
		}
	}
}

void UExtendedDebugHelpers::DrawDebugLineTraceMultiEx(const UWorld* World, const FVector& Start, const FVector& End, EDrawDebugTrace::Type DrawDebugType, ESceneDepthPriority DepthPriority, bool bHit, const TArray<FHitResult>& HitResults, FLinearColor TraceColor, FLinearColor TraceHitColor, float Thickness, float PointSize, float DrawTime)
{
	if (DrawDebugType != EDrawDebugTrace::None)
	{
		const bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
		const float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

		if (bHit && HitResults.Last().bBlockingHit)
		{
			FVector const BlockingHitPoint = HitResults.Last().ImpactPoint;
			DrawDebugLine(World, Start, BlockingHitPoint, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority, Thickness);
			DrawDebugLine(World, BlockingHitPoint, End, TraceHitColor.ToFColor(true), bPersistent, LifeTime, DepthPriority, Thickness);
		}
		else
		{
			DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority, Thickness);
		}
		
		for (int32 HitIdx = 0; HitIdx < HitResults.Num(); ++HitIdx)
		{
			FHitResult const& Hit = HitResults[HitIdx];
			DrawDebugPoint(World, Hit.ImpactPoint, PointSize, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime, DepthPriority);
		}
	}
}

void UExtendedDebugHelpers::DrawDebugBoxTraceSingleEx(const UWorld* World, const FVector& Start, const FVector& End, const FVector& HalfSize, const FRotator& Orientation, EDrawDebugTrace::Type DrawDebugType, ESceneDepthPriority DepthPriority, bool bHit, const FHitResult& HitResult, FLinearColor TraceColor, FLinearColor TraceHitColor, float PointSize, float DrawTime)
{
	if (DrawDebugType != EDrawDebugTrace::None && (World != nullptr))
	{
		const bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
		const float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

		if (bHit && HitResult.bBlockingHit)
		{
			DrawDebugSweptBox(World, Start, HitResult.Location, Orientation, HalfSize, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
			DrawDebugSweptBox(World, HitResult.Location, End, Orientation, HalfSize, TraceHitColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
			DrawDebugPoint(World, HitResult.ImpactPoint, PointSize, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
		}
		else
		{
			DrawDebugSweptBox(World, Start, End, Orientation, HalfSize, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
		}
	}
}

void UExtendedDebugHelpers::DrawDebugBoxTraceMultiEx(const UWorld* World, const FVector& Start, const FVector& End, const FVector& HalfSize, const FRotator& Orientation, EDrawDebugTrace::Type DrawDebugType, ESceneDepthPriority DepthPriority, bool bHit, const TArray<FHitResult>& HitResults, FLinearColor TraceColor, FLinearColor TraceHitColor, float PointSize, float DrawTime)
{
	if (DrawDebugType != EDrawDebugTrace::None && (World != nullptr))
	{
		const bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
		const float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

		if (bHit && HitResults.Last().bBlockingHit)
		{
			FVector const BlockingHitPoint = HitResults.Last().Location;
			DrawDebugSweptBox(World, Start, BlockingHitPoint, Orientation, HalfSize, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
			DrawDebugSweptBox(World, BlockingHitPoint, End, Orientation, HalfSize, TraceHitColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
		}
		else
		{
			DrawDebugSweptBox(World, Start, End, Orientation, HalfSize, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
		}

		for (int32 HitIdx = 0; HitIdx < HitResults.Num(); ++HitIdx)
		{
			FHitResult const& Hit = HitResults[HitIdx];
			DrawDebugPoint(World, Hit.ImpactPoint, PointSize, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime, DepthPriority);
		}
	}
}

void UExtendedDebugHelpers::DrawDebugSphereTraceSingleEx(const UWorld* World, const FVector& Start, const FVector& End, float Radius, EDrawDebugTrace::Type DrawDebugType, ESceneDepthPriority DepthPriority, bool bHit, const FHitResult& HitResult, FLinearColor TraceColor, FLinearColor TraceHitColor, float PointSize, float DrawTime)
{
	if (DrawDebugType != EDrawDebugTrace::None)
	{
		const bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
		const float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

		if (bHit && HitResult.bBlockingHit)
		{
			DrawDebugSweptSphere(World, Start, HitResult.Location, Radius, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
			DrawDebugSweptSphere(World, HitResult.Location, End, Radius, TraceHitColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
			DrawDebugPoint(World, HitResult.ImpactPoint, PointSize, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
		}
		else
		{
			DrawDebugSweptSphere(World, Start, End, Radius, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
		}
	}
}

void UExtendedDebugHelpers::DrawDebugSphereTraceMultiEx(const UWorld* World, const FVector& Start, const FVector& End, float Radius, EDrawDebugTrace::Type DrawDebugType, ESceneDepthPriority DepthPriority, bool bHit, const TArray<FHitResult>& HitResults, FLinearColor TraceColor, FLinearColor TraceHitColor, float PointSize, float DrawTime)
{
	if (DrawDebugType != EDrawDebugTrace::None)
	{
		const bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
		const float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

		if (bHit && HitResults.Last().bBlockingHit)
		{
			FVector const BlockingHitPoint = HitResults.Last().Location;
			DrawDebugSweptSphere(World, Start, BlockingHitPoint, Radius, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
			DrawDebugSweptSphere(World, BlockingHitPoint, End, Radius, TraceHitColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
		}
		else
		{
			DrawDebugSweptSphere(World, Start, End, Radius, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
		}

		for (int32 HitIdx = 0; HitIdx < HitResults.Num(); ++HitIdx)
		{
			FHitResult const& Hit = HitResults[HitIdx];
			DrawDebugPoint(World, Hit.ImpactPoint, PointSize, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime, DepthPriority);
		}
	}
}

void UExtendedDebugHelpers::DrawDebugCapsuleTraceSingleEx(const UWorld* World, const FVector& Start, const FVector& End, float Radius, float HalfHeight, EDrawDebugTrace::Type DrawDebugType, ESceneDepthPriority DepthPriority, bool bHit, const FHitResult& HitResult, FLinearColor TraceColor, FLinearColor TraceHitColor, float PointSize, float DrawTime)
{
	if (DrawDebugType != EDrawDebugTrace::None)
	{
		const bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
		const float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

		if (bHit && HitResult.bBlockingHit)
		{
			DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
			DrawDebugCapsule(World, HitResult.Location, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
			DrawDebugLine(World, Start, HitResult.Location, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
			DrawDebugPoint(World, HitResult.ImpactPoint, PointSize, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);

			DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat::Identity, TraceHitColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
			DrawDebugLine(World, HitResult.Location, End, TraceHitColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
		}
		else
		{
			DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
			DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
			DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
		}
	}
}

void UExtendedDebugHelpers::DrawDebugCapsuleTraceMultiEx(const UWorld* World, const FVector& Start, const FVector& End, float Radius, float HalfHeight, EDrawDebugTrace::Type DrawDebugType, ESceneDepthPriority DepthPriority, bool bHit, const TArray<FHitResult>& HitResults, FLinearColor TraceColor, FLinearColor TraceHitColor, float PointSize, float DrawTime)
{
	if (DrawDebugType != EDrawDebugTrace::None)
	{
		const bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
		const float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

		if (bHit && HitResults.Last().bBlockingHit)
		{
			FVector const BlockingHitPoint = HitResults.Last().Location;
			DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
			DrawDebugCapsule(World, BlockingHitPoint, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
			DrawDebugLine(World, Start, BlockingHitPoint, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);

			DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat::Identity, TraceHitColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
			DrawDebugLine(World, BlockingHitPoint, End, TraceHitColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
		}
		else
		{
			DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
			DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
			DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistent, LifeTime, DepthPriority);
		}

		for (int32 HitIdx = 0; HitIdx < HitResults.Num(); ++HitIdx)
		{
			FHitResult const& Hit = HitResults[HitIdx];
			DrawDebugPoint(World, Hit.ImpactPoint, PointSize, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime, DepthPriority);
		}
	}
}
