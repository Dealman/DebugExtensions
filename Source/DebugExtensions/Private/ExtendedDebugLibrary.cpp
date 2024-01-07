// Copyright 2023 'Dealman' - All Rights Reserved

#include "ExtendedDebugLibrary.h"
#include "ExtendedDebugHelpers.h"
#include "UnrealEngine.h"
#include "Engine/StaticMesh.h"
#include "StaticMeshDescription.h"
#include "MeshDescription.h"
#include "UObject/Package.h"
#include "Misc/ConfigCacheIni.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Engine/HitResult.h"
#include "Kismet/GameplayStatics.h"
#include "Math/RotationMatrix.h"
#include "Engine/LocalPlayer.h"
#include "Engine/GameViewportClient.h"
#include "Engine/Console.h"
#include "Blueprint/BlueprintSupport.h"
#include "HAL/IConsoleManager.h"
// START OF EXTENDED NATIVE DRAWING METHODS

void UExtendedDebugLibrary::DrawDebugPointEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Location, float Size, FLinearColor DebugColor, ESceneDepthPriority DepthPriority, bool bIsPersistent, float Duration)
{
#if ENABLE_DRAW_DEBUG
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		if (!WorldTransform.EqualsNoScale(FTransform::Identity))
		{
			Location = WorldTransform.TransformPosition(Location);
		}
		
		DrawDebugPoint(World, Location, Size, DebugColor.ToFColor(true), bIsPersistent, Duration, DepthPriority);
	}
#endif
}

void UExtendedDebugLibrary::DrawDebugLineEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, FLinearColor DebugColor, ESceneDepthPriority DepthPriority, bool bIsPersistent, float Duration, float Thickness)
{
#if ENABLE_DRAW_DEBUG
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull); World != nullptr)
	{
		if (!WorldTransform.EqualsNoScale(FTransform::Identity))
		{
			Start = WorldTransform.TransformPosition(Start);
			End = WorldTransform.TransformPosition(End);
		}
		
		DrawDebugLine(World, Start, End, DebugColor.ToFColor(true), bIsPersistent, Duration, DepthPriority, Thickness);
	}
#endif
}

void UExtendedDebugLibrary::DrawDebugCircleEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Center, float Radius,int32 Segments, FLinearColor DebugColor, FVector YAxis, FVector ZAxis, bool bDrawAxis, ESceneDepthPriority DepthPriority, bool bIsPersistent, float Duration, float Thickness)
{
#if ENABLE_DRAW_DEBUG
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull); World != nullptr)
	{
		if (!WorldTransform.EqualsNoScale(FTransform::Identity))
		{
			Center = WorldTransform.TransformPosition(Center);
		}
		
		DrawDebugCircle(World, Center, Radius, Segments, DebugColor.ToFColor(true), bIsPersistent, Duration, DepthPriority, Thickness, YAxis, ZAxis, bDrawAxis);
	}
#endif
}

void UExtendedDebugLibrary::DrawDebugArrowEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector Target, float ArrowSize, FLinearColor DebugColor, ESceneDepthPriority DepthPriority, bool bIsPersistent, float Duration, float Thickness)
{
#if ENABLE_DRAW_DEBUG
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull); World != nullptr)
	{
		if (!WorldTransform.EqualsNoScale(FTransform::Identity))
		{
			Start = WorldTransform.TransformPosition(Start);
			Target = WorldTransform.TransformPosition(Target);
		}
		
		DrawDebugDirectionalArrow(World, Start, Target, ArrowSize, DebugColor.ToFColor(true), bIsPersistent, Duration, DepthPriority, Thickness);
	}
#endif
}

void UExtendedDebugLibrary::DrawDebugBoxEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Center, FVector Extent, const FRotator Rotation, FLinearColor DebugColor, ESceneDepthPriority DepthPriority, bool bIsPersistent, float Duration, float Thickness)
{
#if ENABLE_DRAW_DEBUG
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull); World != nullptr)
	{
		if (!WorldTransform.EqualsNoScale(FTransform::Identity))
		{
			Center = WorldTransform.TransformPosition(Center);
		}
		
		if (Rotation == FRotator::ZeroRotator)
		{
			DrawDebugBox(World, Center, Extent, DebugColor.ToFColor(true), bIsPersistent, Duration, DepthPriority, Thickness);
		}
		else
		{
			DrawDebugBox(World, Center, Extent, Rotation.Quaternion(), DebugColor.ToFColor(true), bIsPersistent, Duration, DepthPriority, Thickness);
		}
	}
#endif
}

void UExtendedDebugLibrary::DrawDebugCoordinateSystemEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Location, FRotator Rotation, float Size, ESceneDepthPriority DepthPriority, bool bIsPersistent, float Duration, float Thickness)
{
#if ENABLE_DRAW_DEBUG
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull); World != nullptr)
	{
		if (!WorldTransform.EqualsNoScale(FTransform::Identity))
		{
			Location = WorldTransform.TransformPosition(Location);
		}
		
		DrawDebugCoordinateSystem(World, Location, Rotation, Size, bIsPersistent, Duration, DepthPriority, Thickness);
	}
#endif
}

void UExtendedDebugLibrary::DrawDebugSphereEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Center, float Radius, int32 Segments, FLinearColor DebugColor, ESceneDepthPriority DepthPriority, bool bIsPersistent, float Duration, float Thickness)
{
#if ENABLE_DRAW_DEBUG
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull); World != nullptr)
	{
		if (!WorldTransform.EqualsNoScale(FTransform::Identity))
		{
			Center = WorldTransform.TransformPosition(Center);
		}
		
		DrawDebugSphere(World, Center, Radius, Segments, DebugColor.ToFColor(true), bIsPersistent, Duration, DepthPriority, Thickness);
	}
#endif
}

void UExtendedDebugLibrary::DrawDebugCylinderEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Bottom,	FVector Top, float Radius, int32 Segments, FLinearColor DebugColor, ESceneDepthPriority DepthPriority, bool bIsPersistent, float Duration, float Thickness)
{
#if ENABLE_DRAW_DEBUG
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull); World != nullptr)
	{
		if (!WorldTransform.EqualsNoScale(FTransform::Identity))
		{
			Bottom = WorldTransform.TransformPosition(Bottom);
			Top = WorldTransform.TransformPosition(Top);
		}
		
		DrawDebugCylinder(World, Bottom, Top, Radius, Segments, DebugColor.ToFColor(true), bIsPersistent, Duration, DepthPriority, Thickness);
	}
#endif
}

void UExtendedDebugLibrary::DrawDebugConeInDegreesEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Origin, FVector Direction, float Length, float AngleWidth, float AngleHeight, int32 Segments, FLinearColor DebugColor, ESceneDepthPriority DepthPriority, bool bIsPersistent, float Duration, float Thickness)
{
#if ENABLE_DRAW_DEBUG
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull); World != nullptr)
	{
		if (!WorldTransform.EqualsNoScale(FTransform::Identity))
		{
			Origin = WorldTransform.TransformPosition(Origin);
			Direction = WorldTransform.TransformPosition(Direction);
		}
		
		DrawDebugCone(World, Origin, Direction, Length, FMath::DegreesToRadians(AngleWidth), FMath::DegreesToRadians(AngleHeight), Segments, DebugColor.ToFColor(true), bIsPersistent, Duration, DepthPriority, Thickness);
	}
#endif
}

void UExtendedDebugLibrary::DrawDebugCapsuleEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Center, FRotator Rotation, float HalfHeight, float Radius, FLinearColor DebugColor, ESceneDepthPriority DepthPriority, bool bIsPersistent, float Duration, float Thickness)
{
#if ENABLE_DRAW_DEBUG
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull); World != nullptr)
	{
		if (!WorldTransform.EqualsNoScale(FTransform::Identity))
		{
			Center = WorldTransform.TransformPosition(Center);
		}
		
		DrawDebugCapsule(World, Center, HalfHeight, Radius, Rotation.Quaternion(), DebugColor.ToFColor(true), bIsPersistent, Duration, DepthPriority, Thickness);
	}
#endif
}

void UExtendedDebugLibrary::DrawDebugFrustumEx(const UObject* WorldContextObject, const FTransform WorldTransform, FTransform Transform, FLinearColor DebugColor, ESceneDepthPriority DepthPriority, bool bIsPersistent, float Duration, float Thickness)
{
#if ENABLE_DRAW_DEBUG
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull); World != nullptr)
	{
		if (Transform.IsRotationNormalized())
		{
			if (!WorldTransform.EqualsNoScale(FTransform::Identity))
			{
				const FVector LocalLocation = WorldTransform.TransformPosition(Transform.GetLocation());
				Transform.SetLocation(LocalLocation);
			}

			const FMatrix FrustumToWorld =  Transform.ToMatrixWithScale();
			DrawDebugFrustum(World, FrustumToWorld, DebugColor.ToFColor(true), bIsPersistent, Duration, DepthPriority, Thickness);
		}
	}
#endif
}

void UExtendedDebugLibrary::DrawDebugCameraEx(const ACameraActor* CameraActor, float Size, FLinearColor DebugColor, ESceneDepthPriority DepthPriority, bool bIsPersistent, float Duration)
{
#if ENABLE_DRAW_DEBUG
	if(IsValid(CameraActor))
	{
		const UWorld* CameraWorld = CameraActor->GetWorld();
		const FVector CameraLocation = CameraActor->GetActorLocation();
		const FRotator CameraRotation = CameraActor->GetActorRotation();
		const float CameraFOV = CameraActor->GetCameraComponent()->FieldOfView;
		DrawDebugCamera(CameraWorld, CameraLocation, CameraRotation, CameraFOV, Size, DebugColor.ToFColor(true), bIsPersistent, Duration, DepthPriority);
	}
#endif
}

void UExtendedDebugLibrary::DrawDebugFloatHistoryTransformEx(const UObject* WorldContextObject, const FTransform WorldTransform, const FDebugFloatHistory& FloatHistory, FTransform Transform, FVector2D DrawSize, FLinearColor DebugColor, ESceneDepthPriority DepthPriority, bool bIsPersistent, float Duration)
{
#if ENABLE_DRAW_DEBUG
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull); World != nullptr)
	{
		if (!WorldTransform.EqualsNoScale(FTransform::Identity))
		{
			const FVector LocalLocation = WorldTransform.TransformPosition(Transform.GetLocation());
			Transform.SetLocation(LocalLocation);
		}
		
		DrawDebugFloatHistory(*World, FloatHistory, Transform, DrawSize, DebugColor.ToFColor(true), bIsPersistent, Duration, DepthPriority);
	}
#endif
}

void UExtendedDebugLibrary::DrawDebugFloatHistoryLocationEx(const UObject* WorldContextObject, const FTransform WorldTransform, const FDebugFloatHistory& FloatHistory, FVector Location, FVector2D DrawSize, FLinearColor DebugColor, ESceneDepthPriority DepthPriority, bool bIsPersistent, float Duration)
{
#if ENABLE_DRAW_DEBUG
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull); World != nullptr)
	{
		if (!WorldTransform.EqualsNoScale(FTransform::Identity))
		{
			Location = WorldTransform.TransformPosition(Location);
		}
		
		DrawDebugFloatHistory(*World, FloatHistory, Location, DrawSize, DebugColor.ToFColor(true), bIsPersistent, Duration, DepthPriority);
	}
#endif
}

// END OF EXTENDED NATIVE DRAWING METHODS

// START OF NEW DRAWING METHODS

void UExtendedDebugLibrary::DrawDebugMesh(const UObject* WorldContextObject, UStaticMesh* StaticMesh, const FTransform WorldTransform, FVector Location, FRotator Rotation, int32 LOD, FLinearColor DebugColor, ESceneDepthPriority DepthPriority, bool bIsPersistent, float Duration, float Thickness)
{
	// TODO: Optimization - maybe cache the edge vertex positions instead of doing it at runtime instead check of changes and update if necessary
	#if ENABLE_DRAW_DEBUG
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		if (!WorldTransform.EqualsNoScale(FTransform::Identity))
		{
			Location = WorldTransform.TransformPosition(Location);
		}
		
		if (StaticMesh != nullptr)
		{
			LOD = (LOD <= StaticMesh->GetNumLODs()) ? LOD : 0;
			UStaticMeshDescription* MeshDescription = StaticMesh->GetStaticMeshDescription(LOD);
			const FEdgeArray& EdgeArray = MeshDescription->Edges();

			for (const FEdgeID EdgeID : EdgeArray.GetElementIDs())
			{
				TArray<FVertexID> EdgeVertices;
				MeshDescription->GetEdgeVertices(EdgeID, EdgeVertices);
				FVector EdgeStart = MeshDescription->GetVertexPosition(EdgeVertices[0]);
				FVector EdgeEnd = MeshDescription->GetVertexPosition(EdgeVertices[1]);
				DrawDebugLine(World, Location + EdgeStart, Location + EdgeEnd, DebugColor.ToFColor(true), bIsPersistent, Duration, DepthPriority, Thickness);
			}
		}
	}
#endif
}

// END OF NEW DRAWING METHODS

// START OF NEW TRACING METHODS

bool UExtendedDebugLibrary::LineTraceSingleEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, bool bTraceComplex, bool bIgnoreSelf, ETraceTypeQuery TraceChannel, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TraceThickness, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	ECollisionChannel CollisionChannel = UEngineTypes::ConvertToCollisionChannel(TraceChannel);

	static const FName LineTraceSingleName(TEXT("LineTraceSingleExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(LineTraceSingleName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->LineTraceSingleByChannel(HitResult, Start, End, CollisionChannel, Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugLineTraceSingleEx(World, Start, End, DrawDebugType, TraceDepthPriority, bHit, HitResult, TraceColor, TraceHitColor, TraceThickness, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::LineTraceSingleByProfile(const UObject* WorldContextObject,	const FTransform WorldTransform, FVector Start, FVector End, bool bTraceComplex, bool bIgnoreSelf, FName ProfileName, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TraceThickness, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}

	static const FName LineTraceSingleName(TEXT("LineTraceSingleByProfileExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(LineTraceSingleName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->LineTraceSingleByProfile(HitResult, Start, End, ProfileName, Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugLineTraceSingleEx(World, Start, End, DrawDebugType, TraceDepthPriority, bHit, HitResult, TraceColor, TraceHitColor, TraceThickness, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::LineTraceSingleForObjectsEx(const UObject* WorldContextObject, const FTransform WorldTransform,	FVector Start, FVector End, bool bTraceComplex, bool bIgnoreSelf, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor,	FLinearColor TraceHitColor, float TraceThickness, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}

	static const FName LineTraceSingleName(TEXT("LineTraceSingleForObjectsExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(LineTraceSingleName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	FCollisionObjectQueryParams ObjectParams = UExtendedDebugHelpers::ConfigureCollisionObjectParamsEx(ObjectTypes);
	if (ObjectParams.IsValid() == false)
	{
		UE_LOG(LogBlueprintUserMessages, Warning, TEXT("Invalid object types"));
		return false;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->LineTraceSingleByObjectType(HitResult, Start, End, ObjectParams, Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugLineTraceSingleEx(World, Start, End, DrawDebugType, TraceDepthPriority, bHit, HitResult, TraceColor, TraceHitColor, TraceThickness, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::LineTraceMulti(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, bool bTraceComplex, bool bIgnoreSelf, ETraceTypeQuery TraceChannel, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TraceThickness, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	ECollisionChannel CollisionChannel = UEngineTypes::ConvertToCollisionChannel(TraceChannel);

	static const FName LineTraceMultiName(TEXT("LineTraceMultiExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(LineTraceMultiName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->LineTraceMultiByChannel(HitResults, Start, End, CollisionChannel, Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugLineTraceMultiEx(World, Start, End, DrawDebugType, TraceDepthPriority, bHit, HitResults, TraceColor, TraceHitColor, TraceThickness, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::LineTraceMultiByProfile(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, bool bTraceComplex, bool bIgnoreSelf, FName ProfileName, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TraceThickness, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	static const FName LineTraceMultiName(TEXT("LineTraceMultiByProfileExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(LineTraceMultiName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->LineTraceMultiByProfile(HitResults, Start, End, ProfileName, Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugLineTraceMultiEx(World, Start, End, DrawDebugType, TraceDepthPriority, bHit, HitResults, TraceColor, TraceHitColor, TraceThickness, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::LineTraceMultiForObjects(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, bool bTraceComplex, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TraceThickness, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	static const FName LineTraceMultiName(TEXT("LineTraceMultiForObjectsExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(LineTraceMultiName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	FCollisionObjectQueryParams ObjectParams = UExtendedDebugHelpers::ConfigureCollisionObjectParamsEx(ObjectTypes);
	if (ObjectParams.IsValid() == false)
	{
		UE_LOG(LogBlueprintUserMessages, Warning, TEXT("Invalid object types"));
		return false;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->LineTraceMultiByObjectType(HitResults, Start, End, ObjectParams, Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugLineTraceMultiEx(World, Start, End, DrawDebugType, TraceDepthPriority, bHit, HitResults, TraceColor, TraceHitColor, TraceThickness, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::BoxTraceSingleEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, const FVector HalfSize, const FRotator Orientation, bool bTraceComplex, bool bIgnoreSelf, ETraceTypeQuery TraceChannel, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	static const FName BoxTraceSingleName(TEXT("BoxTraceSingleExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(BoxTraceSingleName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->SweepSingleByChannel(HitResult, Start, End, Orientation.Quaternion(), UEngineTypes::ConvertToCollisionChannel(TraceChannel), FCollisionShape::MakeBox(HalfSize), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugBoxTraceSingleEx(World, Start, End, HalfSize, Orientation, DrawDebugType, TraceDepthPriority, bHit, HitResult, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::BoxTraceSingleByProfileEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, const FVector HalfSize, const FRotator Orientation, bool bTraceComplex, bool bIgnoreSelf, FName ProfileName, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	static const FName BoxTraceSingleName(TEXT("BoxTraceSingleByProfileExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(BoxTraceSingleName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	bool const bHit = World ? World->SweepSingleByProfile(HitResult, Start, End, Orientation.Quaternion(), ProfileName, FCollisionShape::MakeBox(HalfSize), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugBoxTraceSingleEx(World, Start, End, HalfSize, Orientation, DrawDebugType, TraceDepthPriority, bHit, HitResult, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::BoxTraceSingleForObjectsEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, const FVector HalfSize, const FRotator Orientation, bool bTraceComplex, bool bIgnoreSelf, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	static const FName BoxTraceSingleName(TEXT("BoxTraceSingleForObjectsExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(BoxTraceSingleName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	TArray<TEnumAsByte<ECollisionChannel>> CollisionObjectTraces;
	CollisionObjectTraces.AddUninitialized(ObjectTypes.Num());

	FCollisionObjectQueryParams ObjectParams = UExtendedDebugHelpers::ConfigureCollisionObjectParamsEx(ObjectTypes);
	if (ObjectParams.IsValid() == false)
	{
		UE_LOG(LogBlueprintUserMessages, Warning, TEXT("Invalid object types"));
		return false;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->SweepSingleByObjectType(HitResult, Start, End, Orientation.Quaternion(), ObjectParams, FCollisionShape::MakeBox(HalfSize), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugBoxTraceSingleEx(World, Start, End, HalfSize, Orientation, DrawDebugType, TraceDepthPriority, bHit, HitResult, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::BoxTraceMultiEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, FVector HalfSize, const FRotator Orientation, bool bTraceComplex, bool bIgnoreSelf, ETraceTypeQuery TraceChannel, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	static const FName BoxTraceMultiName(TEXT("BoxTraceMultiExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(BoxTraceMultiName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->SweepMultiByChannel(HitResults, Start, End, Orientation.Quaternion(), UEngineTypes::ConvertToCollisionChannel(TraceChannel), FCollisionShape::MakeBox(HalfSize), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugBoxTraceMultiEx(World, Start, End, HalfSize, Orientation, DrawDebugType, TraceDepthPriority, bHit, HitResults, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::BoxTraceMultiByProfileEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, FVector HalfSize, const FRotator Orientation, bool bTraceComplex, bool bIgnoreSelf, FName ProfileName, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	static const FName BoxTraceMultiName(TEXT("BoxTraceMultiByProfileExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(BoxTraceMultiName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->SweepMultiByProfile(HitResults, Start, End, Orientation.Quaternion(), ProfileName, FCollisionShape::MakeBox(HalfSize), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugBoxTraceMultiEx(World, Start, End, HalfSize, Orientation, DrawDebugType, TraceDepthPriority, bHit, HitResults, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::BoxTraceMultiForObjectsEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, const FVector HalfSize, const FRotator Orientation, bool bTraceComplex, bool bIgnoreSelf, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	static const FName BoxTraceMultiName(TEXT("BoxTraceMultiForObjectsExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(BoxTraceMultiName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	FCollisionObjectQueryParams ObjectParams = UExtendedDebugHelpers::ConfigureCollisionObjectParamsEx(ObjectTypes);
	if (ObjectParams.IsValid() == false)
	{
		UE_LOG(LogBlueprintUserMessages, Warning, TEXT("Invalid object types"));
		return false;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->SweepMultiByObjectType(HitResults, Start, End, Orientation.Quaternion(), ObjectParams, FCollisionShape::MakeBox(HalfSize), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugBoxTraceMultiEx(World, Start, End, HalfSize, Orientation, DrawDebugType, TraceDepthPriority, bHit, HitResults, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::SphereTraceSingleEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, bool bTraceComplex, bool bIgnoreSelf, ETraceTypeQuery TraceChannel, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	ECollisionChannel CollisionChannel = UEngineTypes::ConvertToCollisionChannel(TraceChannel);

	static const FName SphereTraceSingleName(TEXT("SphereTraceSingleExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(SphereTraceSingleName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, CollisionChannel, FCollisionShape::MakeSphere(Radius), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugSphereTraceSingleEx(World, Start, End, Radius, DrawDebugType, TraceDepthPriority, bHit, HitResult, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::SphereTraceSingleByProfileEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, bool bTraceComplex, bool bIgnoreSelf, FName ProfileName, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	static const FName SphereTraceSingleName(TEXT("SphereTraceSingleByProfileExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(SphereTraceSingleName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->SweepSingleByProfile(HitResult, Start, End, FQuat::Identity, ProfileName, FCollisionShape::MakeSphere(Radius), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugSphereTraceSingleEx(World, Start, End, Radius, DrawDebugType, TraceDepthPriority, bHit, HitResult, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::SphereTraceSingleForObjectsEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, bool bTraceComplex, bool bIgnoreSelf, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	static const FName SphereTraceSingleName(TEXT("SphereTraceSingleForObjectsExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(SphereTraceSingleName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	FCollisionObjectQueryParams ObjectParams = UExtendedDebugHelpers::ConfigureCollisionObjectParamsEx(ObjectTypes);
	if (ObjectParams.IsValid() == false)
	{
		UE_LOG(LogBlueprintUserMessages, Warning, TEXT("Invalid object types"));
		return false;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->SweepSingleByObjectType(HitResult, Start, End, FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(Radius), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugSphereTraceSingleEx(World, Start, End, Radius, DrawDebugType, TraceDepthPriority, bHit, HitResult, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::SphereTraceMultiEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, bool bTraceComplex, bool bIgnoreSelf, ETraceTypeQuery TraceChannel, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	ECollisionChannel CollisionChannel = UEngineTypes::ConvertToCollisionChannel(TraceChannel);

	static const FName SphereTraceMultiName(TEXT("SphereTraceMultiExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(SphereTraceMultiName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, CollisionChannel, FCollisionShape::MakeSphere(Radius), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugSphereTraceMultiEx(World, Start, End, Radius, DrawDebugType, TraceDepthPriority, bHit, HitResults, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::SphereTraceMultiByProfileEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, bool bTraceComplex, bool bIgnoreSelf, FName ProfileName, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	static const FName SphereTraceMultiName(TEXT("SphereTraceMultiByProfileExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(SphereTraceMultiName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->SweepMultiByProfile(HitResults, Start, End, FQuat::Identity, ProfileName, FCollisionShape::MakeSphere(Radius), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugSphereTraceMultiEx(World, Start, End, Radius, DrawDebugType, TraceDepthPriority, bHit, HitResults, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::SphereTraceMultiForObjectsEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, bool bTraceComplex, bool bIgnoreSelf, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	static const FName SphereTraceMultiName(TEXT("SphereTraceMultiForObjectsExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(SphereTraceMultiName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	FCollisionObjectQueryParams ObjectParams = UExtendedDebugHelpers::ConfigureCollisionObjectParamsEx(ObjectTypes);
	if (ObjectParams.IsValid() == false)
	{
		UE_LOG(LogBlueprintUserMessages, Warning, TEXT("Invalid object types"));
		return false;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->SweepMultiByObjectType(HitResults, Start, End, FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(Radius), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugSphereTraceMultiEx(World, Start, End, Radius, DrawDebugType, TraceDepthPriority, bHit, HitResults, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::CapsuleTraceSingleEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, float HalfHeight, bool bTraceComplex, bool bIgnoreSelf, ETraceTypeQuery TraceChannel, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	ECollisionChannel CollisionChannel = UEngineTypes::ConvertToCollisionChannel(TraceChannel);

	static const FName CapsuleTraceSingleName(TEXT("CapsuleTraceSingleExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(CapsuleTraceSingleName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, CollisionChannel, FCollisionShape::MakeCapsule(Radius, HalfHeight), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugCapsuleTraceSingleEx(World, Start, End, Radius, HalfHeight, DrawDebugType, TraceDepthPriority, bHit, HitResult, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::CapsuleTraceSingleByProfileEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, float HalfHeight, bool bTraceComplex, bool bIgnoreSelf, FName ProfileName, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	static const FName CapsuleTraceSingleName(TEXT("CapsuleTraceSingleByProfileExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(CapsuleTraceSingleName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->SweepSingleByProfile(HitResult, Start, End, FQuat::Identity, ProfileName, FCollisionShape::MakeCapsule(Radius, HalfHeight), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugCapsuleTraceSingleEx(World, Start, End, Radius, HalfHeight, DrawDebugType, TraceDepthPriority, bHit, HitResult, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::CapsuleTraceSingleForObjectsEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, float HalfHeight, bool bTraceComplex, bool bIgnoreSelf, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	static const FName CapsuleTraceSingleName(TEXT("CapsuleTraceSingleForObjectsExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(CapsuleTraceSingleName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	FCollisionObjectQueryParams ObjectParams = UExtendedDebugHelpers::ConfigureCollisionObjectParamsEx(ObjectTypes);
	if (ObjectParams.IsValid() == false)
	{
		UE_LOG(LogBlueprintUserMessages, Warning, TEXT("Invalid object types"));
		return false;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->SweepSingleByObjectType(HitResult, Start, End, FQuat::Identity, ObjectParams, FCollisionShape::MakeCapsule(Radius, HalfHeight), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugCapsuleTraceSingleEx(World, Start, End, Radius, HalfHeight, DrawDebugType, TraceDepthPriority, bHit, HitResult, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::CapsuleTraceMultiEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, float HalfHeight, bool bTraceComplex, bool bIgnoreSelf, ETraceTypeQuery TraceChannel, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	ECollisionChannel CollisionChannel = UEngineTypes::ConvertToCollisionChannel(TraceChannel);

	static const FName CapsuleTraceMultiName(TEXT("CapsuleTraceMultiExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(CapsuleTraceMultiName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, CollisionChannel, FCollisionShape::MakeCapsule(Radius, HalfHeight), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugCapsuleTraceMultiEx(World, Start, End, Radius, HalfHeight, DrawDebugType, TraceDepthPriority, bHit, HitResults, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;	
}

bool UExtendedDebugLibrary::CapsuleTraceMultiByProfileEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, float HalfHeight, bool bTraceComplex, bool bIgnoreSelf, FName ProfileName, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	static const FName CapsuleTraceMultiName(TEXT("CapsuleTraceMultiByProfileExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(CapsuleTraceMultiName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->SweepMultiByProfile(HitResults, Start, End, FQuat::Identity, ProfileName, FCollisionShape::MakeCapsule(Radius, HalfHeight), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugCapsuleTraceMultiEx(World, Start, End, Radius, HalfHeight, DrawDebugType, TraceDepthPriority, bHit, HitResults, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

bool UExtendedDebugLibrary::CapsuleTraceMultiForObjectsEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, float HalfHeight, bool bTraceComplex, bool bIgnoreSelf, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority, FLinearColor TraceColor, FLinearColor TraceHitColor, float TracePointSize, float TraceDrawTime)
{
	if (!WorldTransform.EqualsNoScale(FTransform::Identity))
	{
		Start = WorldTransform.TransformPosition(Start);
		End = WorldTransform.TransformPosition(End);
	}
	
	static const FName CapsuleTraceMultiName(TEXT("CapsuleTraceMultiForObjectsExtended"));
	FCollisionQueryParams Params = UExtendedDebugHelpers::ConfigureCollisionParamsEx(CapsuleTraceMultiName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);

	FCollisionObjectQueryParams ObjectParams = UExtendedDebugHelpers::ConfigureCollisionObjectParamsEx(ObjectTypes);
	if (ObjectParams.IsValid() == false)
	{
		UE_LOG(LogBlueprintUserMessages, Warning, TEXT("Invalid object types"));
		return false;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	bool const bHit = World ? World->SweepMultiByObjectType(HitResults, Start, End, FQuat::Identity, ObjectParams, FCollisionShape::MakeCapsule(Radius, HalfHeight), Params) : false;

#if ENABLE_DRAW_DEBUG
	UExtendedDebugHelpers::DrawDebugCapsuleTraceMultiEx(World, Start, End, Radius, HalfHeight, DrawDebugType, TraceDepthPriority, bHit, HitResults, TraceColor, TraceHitColor, TracePointSize, TraceDrawTime);
#endif

	return bHit;
}

// END OF NEW TRACING METHODS

void UExtendedDebugLibrary::LogStringEx(const UObject* WorldContextObject, const FString& InString, FName CategoryName, TEnumAsByte<ELogVerbosityEx> Verbosity)
{
	const FLogCategory Test = FLogCategory<ELogVerbosity::Type::Log, ELogVerbosity::Type::Log>(CategoryName);
	const APlayerController* PC = (WorldContextObject ? UGameplayStatics::GetPlayerController(WorldContextObject, 0) : nullptr);
	const ULocalPlayer* LocalPlayer = (PC ? Cast<ULocalPlayer>(PC->Player) : nullptr);

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) || USE_LOGGING_IN_SHIPPING
	switch (Verbosity)
	{
	case Fatal:
			if (CategoryName == NAME_None)
			{
				UE_LOG(LogBlueprintUserMessages, Fatal, TEXT("%s"), *InString);
			}
			else
			{
				UE_LOG(Test, Fatal, TEXT("%s"), *InString);
			}
			return;
		case Error:
			if (CategoryName == NAME_None)
			{
				UE_LOG(LogBlueprintUserMessages, Error, TEXT("%s"), *InString);
			}
			else
			{
				UE_LOG(Test, Error, TEXT("%s"), *InString);
			}
			return;
		case Warning:
			if (CategoryName == NAME_None)
			{
				UE_LOG(LogBlueprintUserMessages, Warning, TEXT("%s"), *InString);
			}
			else
			{
				UE_LOG(Test, Warning, TEXT("%s"), *InString);
			}
			return;
		case Display:
			if (CategoryName == NAME_None)
			{
				UE_LOG(LogBlueprintUserMessages, Display, TEXT("%s"), *InString);
			}
			else
			{
				UE_LOG(Test, Display, TEXT("%s"), *InString);
			}
			if (LocalPlayer && LocalPlayer->ViewportClient && LocalPlayer->ViewportClient->ViewportConsole)
			{
				if (CategoryName == NAME_None)
				{
					LocalPlayer->ViewportClient->ViewportConsole->OutputText(InString);
				}
				else
				{
					LocalPlayer->ViewportClient->ViewportConsole->OutputText(FString::Printf(TEXT("[%s]: %s"), *CategoryName.ToString(), *InString));
				}
			}
			return;
		case Log:
			if (CategoryName == NAME_None)
			{
				UE_LOG(LogBlueprintUserMessages, Log, TEXT("%s"), *InString);
			}
			else
			{
				UE_LOG(Test, Log, TEXT("%s"), *InString);
			}
			return;
		case Verbose:
			if (CategoryName == NAME_None)
			{
				UE_LOG(LogBlueprintUserMessages, Verbose, TEXT("%s"), *InString);
			}
			else
			{
				UE_LOG(Test, Verbose, TEXT("%s"), *InString);
			}
			return;
		case VeryVerbose:
			if (CategoryName == NAME_None)
			{
				UE_LOG(LogBlueprintUserMessages, VeryVerbose, TEXT("%s"), *InString);
			}
			else
			{
				UE_LOG(Test, VeryVerbose, TEXT("%s"), *InString);
			}
			return;
		default:
			if (CategoryName == NAME_None)
			{
				UE_LOG(LogBlueprintUserMessages, Log, TEXT("%s"), *InString);
			}
			else
			{
				UE_LOG(Test, Log, TEXT("%s"), *InString);
			}
	}
#endif
}

void UExtendedDebugLibrary::PrintStringEx(const UObject* WorldContextObject, const FString& InString, bool bPrintToScreen, bool bPrintToLog, bool bPrintToConsole, bool bNewerOnTop, FLinearColor TextColor, float Duration, const FName Key, const FVector2D TextScale)
{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) || USE_LOGGING_IN_SHIPPING // Do not Print in Shipping or Test unless explicitly enabled.

	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	FString Prefix;
	if (World)
	{
		if (World->WorldType == EWorldType::PIE)
		{
			switch(World->GetNetMode())
			{
				case NM_Client:
					// GPlayInEditorID 0 is always the server, so 1 will be first client.
					// You want to keep this logic in sync with GeneratePIEViewportWindowTitle and UpdatePlayInEditorWorldDebugString
					Prefix = FString::Printf(TEXT("Client %d: "), static_cast<int>(GPlayInEditorID));
					break;
				case NM_DedicatedServer:
				case NM_ListenServer:
					Prefix = FString::Printf(TEXT("Server: "));
					break;
				case NM_Standalone:
					break;
				default:
				break;
			}
		}
	}

#if DO_BLUEPRINT_GUARD
	static const auto CVarBlamePrintString = IConsoleManager::Get().FindConsoleVariable(TEXT("bp.BlamePrintString"));
	const bool bBlamePrintString = CVarBlamePrintString->GetBool();
	if (bBlamePrintString && !FBlueprintContextTracker::Get().GetCurrentScriptStack().IsEmpty())
	{
		const TArrayView<const FFrame* const> ScriptStack = FBlueprintContextTracker::Get().GetCurrentScriptStack();
		Prefix = FString::Printf(TEXT("Blueprint Object: %s\nBlueprint Function: %s\n%s"), 
			*ScriptStack.Last()->Node->GetPackage()->GetPathName(),
			*ScriptStack.Last()->Node->GetName(),
			*Prefix);
	}
#endif

	const FString FinalDisplayString = Prefix + InString;
	FString FinalLogString = FinalDisplayString;

	static const FBoolConfigValueHelper DisplayPrintStringSource(TEXT("Kismet"), TEXT("bLogPrintStringSource"), GEngineIni);
	if (DisplayPrintStringSource)
	{
		const FString SourceObjectPrefix = FString::Printf(TEXT("[%s] "), *GetNameSafe(WorldContextObject));
		FinalLogString = SourceObjectPrefix + FinalLogString;
	}

	if (bPrintToLog)
	{
		UE_LOG(LogBlueprintUserMessages, Log, TEXT("%s"), *FinalLogString);
	}

	if (bPrintToScreen)
	{
		if (GAreScreenMessagesEnabled)
		{
			if (GConfig && Duration < 0)
			{
				GConfig->GetFloat( TEXT("Kismet"), TEXT("PrintStringDuration"), Duration, GEngineIni );
			}
			uint64 InnerKey = -1;
			if (Key != NAME_None)
			{
				InnerKey = GetTypeHash(Key);
			}
			GEngine->AddOnScreenDebugMessage(InnerKey, Duration, TextColor.ToFColor(true), FinalDisplayString, bNewerOnTop, TextScale);
		}
		else
		{
			UE_LOG(LogBlueprint, VeryVerbose, TEXT("Screen messages disabled (!GAreScreenMessagesEnabled).  Cannot print to screen."));
		}
	}

	if (bPrintToScreen)
	{
		const APlayerController* PC = (WorldContextObject ? UGameplayStatics::GetPlayerController(WorldContextObject, 0) : nullptr);
		const ULocalPlayer* LocalPlayer = (PC ? Cast<ULocalPlayer>(PC->Player) : nullptr);
		if (LocalPlayer && LocalPlayer->ViewportClient && LocalPlayer->ViewportClient->ViewportConsole)
        {
        	LocalPlayer->ViewportClient->ViewportConsole->OutputText(FinalDisplayString);
        }
	}
#endif
}
