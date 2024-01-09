// Copyright 2023 'Dealman' - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CollisionQueryParams.h"
#include "ExtendedDebugHelpers.generated.h"

/**
 * A priority for sorting scene elements by depth.
 * Elements with higher priority occlude elements with lower priority, disregarding distance.
 */
UENUM(BlueprintType)
enum ESceneDepthPriority : int
{
	/* Typically renders behind basic geometry */
	Low,
	/* Typically renders in front of basic geometry */
	Medium,
	/* Untested, but internally referred to as 'Max' */
	High
};

/**
 * Contains static helper methods for drawing traces and setting up collision parameters
 */
//UCLASS()
class DEBUGEXTENSIONS_API ExtendedDebugHelpers// : public UObject
{
	//GENERATED_BODY()
	
public:
	static FCollisionQueryParams ConfigureCollisionParamsEx(FName TraceTag, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, bool bIgnoreSelf, const UObject* WorldContextObject);
	static FCollisionObjectQueryParams ConfigureCollisionObjectParamsEx(const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes);

	static void DrawDebugLineTraceSingleEx(const UWorld* World, const FVector& Start, const FVector& End, EDrawDebugTrace::Type DrawDebugType, ESceneDepthPriority DepthPriority, bool bHit, const FHitResult& HitResult, FLinearColor TraceColor, FLinearColor TraceHitColor, float Thickness, float PointSize, float DrawTime);
	static void DrawDebugLineTraceMultiEx(const UWorld* World, const FVector& Start, const FVector& End, EDrawDebugTrace::Type DrawDebugType, ESceneDepthPriority DepthPriority, bool bHit, const TArray<FHitResult>& HitResults, FLinearColor TraceColor, FLinearColor TraceHitColor, float Thickness, float PointSize, float DrawTime);
	static void DrawDebugBoxTraceSingleEx(const UWorld* World, const FVector& Start, const FVector& End, const FVector& HalfSize, const FRotator& Orientation, EDrawDebugTrace::Type DrawDebugType, ESceneDepthPriority DepthPriority, bool bHit, const FHitResult& HitResult, FLinearColor TraceColor, FLinearColor TraceHitColor, float PointSize, float DrawTime);
	static void DrawDebugBoxTraceMultiEx(const UWorld* World, const FVector& Start, const FVector& End, const FVector& HalfSize, const FRotator& Orientation, EDrawDebugTrace::Type DrawDebugType, ESceneDepthPriority DepthPriority, bool bHit, const TArray<FHitResult>& HitResults, FLinearColor TraceColor, FLinearColor TraceHitColor, float PointSize, float DrawTime);
	static void DrawDebugSphereTraceSingleEx(const UWorld* World, const FVector& Start, const FVector& End, float Radius, EDrawDebugTrace::Type DrawDebugType, ESceneDepthPriority DepthPriority, bool bHit, const FHitResult& HitResult, FLinearColor TraceColor, FLinearColor TraceHitColor, float PointSize, float DrawTime);
	static void DrawDebugSphereTraceMultiEx(const UWorld* World, const FVector& Start, const FVector& End, float Radius, EDrawDebugTrace::Type DrawDebugType, ESceneDepthPriority DepthPriority, bool bHit, const TArray<FHitResult>& HitResults, FLinearColor TraceColor, FLinearColor TraceHitColor, float PointSize, float DrawTime);
	static void DrawDebugCapsuleTraceSingleEx(const UWorld* World, const FVector& Start, const FVector& End, float Radius, float HalfHeight, EDrawDebugTrace::Type DrawDebugType, ESceneDepthPriority DepthPriority, bool bHit, const FHitResult& HitResult, FLinearColor TraceColor, FLinearColor TraceHitColor, float PointSize, float DrawTime);
	static void DrawDebugCapsuleTraceMultiEx(const UWorld* World, const FVector& Start, const FVector& End, float Radius, float HalfHeight, EDrawDebugTrace::Type DrawDebugType, ESceneDepthPriority DepthPriority, bool bHit, const TArray<FHitResult>& HitResults, FLinearColor TraceColor, FLinearColor TraceHitColor, float PointSize, float DrawTime);
};
