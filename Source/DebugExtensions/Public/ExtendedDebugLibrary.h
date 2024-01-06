// Copyright 2023 'Dealman' - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ExtendedDebugHelpers.h"
#include "ExtendedDebugLibrary.generated.h"

UENUM(BlueprintType)
enum ELogVerbosityEx : uint8
{
	/** Not used */
	NoLogging		= 0,
	/** Always prints a fatal error to console (and log file) and crashes (even if logging is disabled) */
	Fatal			= 1,
	/** 
	 * Prints an error to console (and log file). 
	 * Commandlets and the editor collect and report errors. Error messages result in commandlet failure.
	 */
	Error			= 2,
	/** 
	 * Prints a warning to console (and log file).
	 * Commandlets and the editor collect and report warnings. Warnings can be treated as an error.
	 */
	Warning			= 3,
	/** Prints a message to console (and log file) */
	Display			= 4,
	/** Prints a message to a log file (does not print to console) */
	Log				= 5,
	/** 
	 * Prints a verbose message to a log file (if Verbose logging is enabled for the given category, 
	 * usually used for detailed logging) 
	 */
	Verbose			= 6,
	/** 
	 * Prints a verbose message to a log file (if VeryVerbose logging is enabled, 
	 * usually used for detailed logging that would otherwise spam output) 
	 */
	VeryVerbose		= 7
};

/**
 * Extends some native debug drawing methods with more options, descriptions as well as adding some new methods.
 */
UCLASS()
class DEBUGEXTENSIONS_API UExtendedDebugLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

#pragma region Extended Native Drawing Methods
	/** 
	* Draw a Debug Point - Extended Version of the Native 'DrawDebugPoint'
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Location				Location of the point, world/local space is determined by actor reference
	* @param Size					Size of the point
	* @param DebugColor				Color of the point in sRGB
	* @param DepthPriority			Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param bIsPersistent			Whether the point should persist after drawing once, call 'FlushPersistentDebugLines' to clean them up
	* @param Duration				How long the point will be drawn for in seconds, unrelated to 'bIsPersistent'
	*/
	UFUNCTION(BlueprintCallable, Category="Rendering|Debug|Extended", meta=(WorldContext="WorldContextObject", AdvancedDisplay="DepthPriority,bIsPersistent,Duration", DevelopmentOnly))
	static void DrawDebugPointEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Location=FVector::ZeroVector, float Size=12.f, FLinearColor DebugColor=FLinearColor::White, ESceneDepthPriority DepthPriority=Low, bool bIsPersistent=false, float Duration=0.f);
	
	/**
	* Draw a Debug Line - Extended Version of the Native 'DrawDebugLine'
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the line
	* @param End					End location of the line
	* @param DebugColor				Color of the line in sRGB
	* @param DepthPriority			Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param bIsPersistent			Whether the line should persist after drawing once, call 'FlushPersistentDebugLines' to clean them up
	* @param Duration				How long the line will be drawn for in seconds, unrelated to 'bIsPersistent'
	* @param Thickness				Thickness of the drawn line
	*/
	UFUNCTION(BlueprintCallable, Category="Rendering|Debug|Extended", meta=(WorldContext="WorldContextObject", AdvancedDisplay="DepthPriority,bIsPersistent,Duration,Thickness", DevelopmentOnly))
	static void DrawDebugLineEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start=FVector::ZeroVector, FVector End=FVector::ZeroVector, FLinearColor DebugColor=FLinearColor::White, ESceneDepthPriority DepthPriority=Low, bool bIsPersistent=false, float Duration=0.f, float Thickness=1.f);

	/** Draw a Debug Circle - Extended Version of the Native 'DrawDebugCircle'
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Center					Center location of the circle
	* @param Radius					Radius of the circle
	* @param Segments				Number of segments the circle should consist of
	* @param DebugColor				Color of the circle in sRGB
	* @param YAxis					Y-Axis of the circle (side)
	* @param ZAxis					Z-Axis of the circle (top)
	* @param bDrawAxis				Whether the axes of the circle should be drawn as well
	* @param DepthPriority			Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param bIsPersistent			Whether the circle should persist after drawing once, call 'FlushPersistentDebugLines' to clean them up
	* @param Duration				How long the circle will be drawn for in seconds, unrelated to 'bIsPersistent'
	* @param Thickness				Thickness of the drawn circle
	*/
	UFUNCTION(BlueprintCallable, Category="Rendering|Debug|Extended", meta=(WorldContext="WorldContextObject", AdvancedDisplay="DepthPriority,bIsPersistent,Duration,Thickness", DevelopmentOnly))
	static void DrawDebugCircleEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Center=FVector::ZeroVector, float Radius=10.f, int32 Segments=12, FLinearColor DebugColor=FLinearColor::White, FVector YAxis=FVector(0.f,1.f,0.f),FVector ZAxis=FVector(0.f,0.f,1.f), bool bDrawAxis=false, ESceneDepthPriority DepthPriority=Low, bool bIsPersistent=false, float Duration=0.f, float Thickness=1.f);
	
	/** Draw a Debug Arrow - Extended Version of the Native 'DrawDebugArrow'
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the arrow
	* @param Target					End location and also the facing target of the arrow
	* @param ArrowSize				Size of the drawn arrow
	* @param DebugColor				Color of the arrow in sRGB
	* @param DepthPriority			Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param bIsPersistent			Whether the arrow should persist after drawing once, call 'FlushPersistentDebugLines' to clean them up
	* @param Duration				How long the arrow will be drawn for in seconds, unrelated to 'bIsPersistent'
	* @param Thickness				Thickness of the drawn arrow
	*/
	UFUNCTION(BlueprintCallable, Category="Rendering|Debug|Extended", meta=(WorldContext="WorldContextObject", AdvancedDisplay="DepthPriority,bIsPersistent,Duration,Thickness", DevelopmentOnly))
	static void DrawDebugArrowEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start=FVector::ZeroVector, FVector Target=FVector::ZeroVector, float ArrowSize=5.f, FLinearColor DebugColor=FLinearColor::White, ESceneDepthPriority DepthPriority=Low, bool bIsPersistent=false, float Duration=0.f, float Thickness=1.f);

	/** Draw a Debug Box - Extended Version of the Native 'DrawDebugBox'
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Center					Center location of the box
	* @param Extent					Extents of the box
	* @param Rotation				Rotation of the box
	* @param DebugColor				Color of the box in sRGB
	* @param DepthPriority			Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param bIsPersistent			Whether the box should persist after drawing once, call 'FlushPersistentDebugLines' to clean them up
	* @param Duration				How long the box will be drawn for in seconds, unrelated to 'bIsPersistent'
	* @param Thickness				Thickness of the drawn box
	*/
	UFUNCTION(BlueprintCallable, Category="Rendering|Debug|Extended", meta=(WorldContext="WorldContextObject", AdvancedDisplay="DepthPriority,bIsPersistent,Duration,Thickness", DevelopmentOnly))
	static void DrawDebugBoxEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Center=FVector::ZeroVector, FVector Extent=FVector::ZeroVector, const FRotator Rotation=FRotator::ZeroRotator, FLinearColor DebugColor=FLinearColor::White, ESceneDepthPriority DepthPriority=Low, bool bIsPersistent=false, float Duration=0.f, float Thickness=1.f);

	/** Draw a Debug Coordinate System - Extended Version of the Native 'DrawDebugCoordinateSystem'
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Location				Location of the coordinate system
	* @param Rotation				Rotation of the coordinate system 
	* @param Size					Size of the coordinate system 
	* @param DepthPriority			Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param bIsPersistent			Whether the coordinate system should persist after drawing once, call 'FlushPersistentDebugLines' to clean them up
	* @param Duration				How long the coordinate system will be drawn for in seconds, unrelated to 'bIsPersistent'
	* @param Thickness				Thickness of the drawn coordinate system
	*/
	UFUNCTION(BlueprintCallable, Category="Rendering|Debug|Extended", meta=(WorldContext="WorldContextObject", AdvancedDisplay="DepthPriority,bIsPersistent,Duration,Thickness", DevelopmentOnly))
	static void DrawDebugCoordinateSystemEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Location=FVector::ZeroVector, FRotator Rotation=FRotator::ZeroRotator, float Size=1.f, ESceneDepthPriority DepthPriority=Low, bool bIsPersistent=false, float Duration=0.f, float Thickness=1.f);

	/** Draw a Debug Sphere - Extended Version of the Native 'DrawDebugSphere'
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Center					Center location of the sphere
	* @param Radius					Radius of the sphere
	* @param Segments				Number of segments the sphere should consist of 
	* @param DebugColor				Color of the sphere in sRGB
	* @param DepthPriority			Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param bIsPersistent			Whether the sphere should persist after drawing once, call 'FlushPersistentDebugLines' to clean them up
	* @param Duration				How long the sphere will be drawn for in seconds, unrelated to 'bIsPersistent'
	* @param Thickness				Thickness of the drawn sphere
	*/
	UFUNCTION(BlueprintCallable, Category="Rendering|Debug|Extended", meta=(WorldContext="WorldContextObject", AdvancedDisplay="DepthPriority,bIsPersistent,Duration,Thickness", DevelopmentOnly))
	static void DrawDebugSphereEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Center=FVector::ZeroVector, float Radius=100.f, int32 Segments=12, FLinearColor DebugColor=FLinearColor::White, ESceneDepthPriority DepthPriority=Low, bool bIsPersistent=false, float Duration=0.f, float Thickness=1.f);

	/** Draw a Debug Cylinder - Extended Version of the Native 'DrawDebugCylinder'
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Bottom					Starting (bottom) location of the cylinder
	* @param Top					End (top) location of the cylinder
	* @param Radius					Radius of the cylinder
	* @param Segments				Number of segments the cylinder should consist of
	* @param DebugColor				Color of the cylinder in sRGB
	* @param DepthPriority			Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param bIsPersistent			Whether the cylinder should persist after drawing once, call 'FlushPersistentDebugLines' to clean them up
	* @param Duration				How long the cylinder will be drawn for in seconds, unrelated to 'bIsPersistent'
	* @param Thickness				Thickness of the drawn cylinder
	*/
	UFUNCTION(BlueprintCallable, Category="Rendering|Debug|Extended", meta=(WorldContext="WorldContextObject", AdvancedDisplay="DepthPriority,bIsPersistent,Duration,Thickness", DevelopmentOnly))
	static void DrawDebugCylinderEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Bottom=FVector::ZeroVector, FVector Top=FVector::ZeroVector, float Radius=100.f, int32 Segments=12, FLinearColor DebugColor = FLinearColor::White, ESceneDepthPriority DepthPriority=Low, bool bIsPersistent=false, float Duration=0.f, float Thickness=1.f);

	/** Draw a Debug Cone with Angles Specified in Degrees - Extended Version of the Native 'DrawDebugConeInDegrees'
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Origin					The origin (start) location of the cone
	* @param Direction				The direction (target) of the cone
	* @param Length					The length of the cone
	* @param AngleWidth				Angle width in degrees
	* @param AngleHeight			Angle height in degrees
	* @param Segments				Number of segments the cone should consist of
	* @param DebugColor				Color of the cone in sRGB
	* @param DepthPriority			Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param bIsPersistent			Whether the cone should persist after drawing once, call 'FlushPersistentDebugLines' to clean them up
	* @param Duration				How long the cone will be drawn for in seconds, unrelated to 'bIsPersistent'
	* @param Thickness				Thickness of the drawn cone
	*/
	UFUNCTION(BlueprintCallable, Category="Rendering|Debug|Extended", meta=(WorldContext="WorldContextObject", DisplayName="Draw Debug Cone Ex", AdvancedDisplay="DepthPriority,bIsPersistent,Duration,Thickness", DevelopmentOnly))
	static void DrawDebugConeInDegreesEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Origin=FVector::ZeroVector, FVector Direction=FVector::ZeroVector, float Length=100.f, float AngleWidth=45.f, float AngleHeight=45.f, int32 Segments=12, FLinearColor DebugColor=FLinearColor::White, ESceneDepthPriority DepthPriority=Low, bool bIsPersistent=false, float Duration=0.f, float Thickness=1.f);

	/** Draw a Debug Capsule - Extended Version of the Native 'DrawDebugCapsule'
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Center					The center location of the capsule
	* @param Rotation				The rotation of the capsule
	* @param HalfHeight				The half-height of the capsule
	* @param Radius					The radius of the capsule
	* @param DebugColor				Color of the capsule in sRGB
	* @param DepthPriority			Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param bIsPersistent			Whether the capsule should persist after drawing once, call 'FlushPersistentDebugLines' to clean them up
	* @param Duration				How long the capsule will be drawn for in seconds, unrelated to 'bIsPersistent'
	* @param Thickness				Thickness of the drawn capsule
	*/
	UFUNCTION(BlueprintCallable, Category="Rendering|Debug|Extended", meta=(WorldContext="WorldContextObject", AdvancedDisplay="DepthPriority,bIsPersistent,Duration,Thickness", DevelopmentOnly))
	static void DrawDebugCapsuleEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Center=FVector::ZeroVector, FRotator Rotation=FRotator::ZeroRotator, float HalfHeight=20.f, float Radius=10.f, FLinearColor DebugColor=FLinearColor::White, ESceneDepthPriority DepthPriority=Low, bool bIsPersistent=false, float Duration=0.f, float Thickness=1.f);

	/** Draw a Debug Frustum - Extended Version of the Native 'DrawDebugFrustum'
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param FrustumTransform		The transform of the frustum
	* @param DebugColor				Color of the capsule in sRGB
	* @param DepthPriority			Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param bIsPersistent			Whether the capsule should persist after drawing once, call 'FlushPersistentDebugLines' to clean them up
	* @param Duration				How long the frustum will be drawn for in seconds, unrelated to 'bIsPersistent'
	* @param Thickness				Thickness of the drawn capsule
	*/
	UFUNCTION(BlueprintCallable, Category="Rendering|Debug|Extended", meta=(WorldContext="WorldContextObject", AdvancedDisplay="DepthPriority,bIsPersistent,Duration,Thickness", DevelopmentOnly))
	static void DrawDebugFrustumEx(const UObject* WorldContextObject, const FTransform WorldTransform, FTransform FrustumTransform=FTransform(), FLinearColor DebugColor=FLinearColor::White, ESceneDepthPriority DepthPriority=Low, bool bIsPersistent=false, float Duration=0.f, float Thickness=1.f);

	/** Draw a Debug Camera Shape - Extended Version of the Native 'DrawDebugCamera'
	*
	* @param CameraActor			Camera Actor reference, draws the debug shape using this actor's location, rotation and FOV
	* @param Size					The size of the camera shape
	* @param DebugColor				Color of the camera shape in sRGB
	* @param DepthPriority			Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param bIsPersistent			Whether the camera shape should persist after drawing once, call 'FlushPersistentDebugLines' to clean them up
	* @param Duration				How long the camera shape will be drawn for in seconds, unrelated to 'bIsPersistent'
	*/
	UFUNCTION(BlueprintCallable, Category="Rendering|Debug|Extended", meta=(AdvancedDisplay="DepthPriority,bIsPersistent,Duration", DevelopmentOnly))
	static void DrawDebugCameraEx(const ACameraActor* CameraActor=nullptr, float Size=10.f, FLinearColor DebugColor=FLinearColor::White, ESceneDepthPriority DepthPriority=Low, bool bIsPersistent=false, float Duration=0.f);
	
	/** Draw a 2D Histogram at Transform - Extended Version of the Native 'DrawDebugFloatHistoryTransform'
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param FloatHistory			FloatHistory struct of which to draw the histogram from. Use 'AddFloatHistorySample' to add entries
	* @param Transform				Transform at which to draw the histogram
	* @param DrawSize				Size of the drawn histogram
	* @param DebugColor				Color of the histogram in sRGB
	* @param DepthPriority			Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param bIsPersistent			Whether the histogram should persist after drawing once, call 'FlushPersistentDebugLines' to clean them up
	* @param Duration				How long the histogram will be drawn for in seconds, unrelated to 'bIsPersistent'
	*/
	UFUNCTION(BlueprintCallable, Category = "Rendering|Debug|Extended", meta=(WorldContext="WorldContextObject", AdvancedDisplay="DepthPriority,bIsPersistent,Duration", DevelopmentOnly))
	static void DrawDebugFloatHistoryTransformEx(const UObject* WorldContextObject, const FTransform WorldTransform, const FDebugFloatHistory& FloatHistory=FDebugFloatHistory(), FTransform Transform=FTransform(), FVector2D DrawSize=FVector2D::ZeroVector, FLinearColor DebugColor=FLinearColor::White, ESceneDepthPriority DepthPriority=Low, bool bIsPersistent=false, float Duration=0.f);
	
	/** Draw a 2D Histogram at Location (will face camera of first player) - Extended Version of the Native 'DrawDebugFloatHistoryLocation'
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param FloatHistory			FloatHistory struct of which to draw the histogram from. Use 'AddFloatHistorySample' to add entries
	* @param Location				Location at which to draw the histogram
	* @param DrawSize				Size of the drawn histogram
	* @param DebugColor				Color of the histogram in sRGB
	* @param DepthPriority			Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param bIsPersistent			Whether the histogram should persist after drawing once, call 'FlushPersistentDebugLines' to clean them up
	* @param Duration				How long the histogram will be drawn for in seconds, unrelated to 'bIsPersistent'
	*/
	UFUNCTION(BlueprintCallable, Category = "Rendering|Debug|Extended", meta=(WorldContext="WorldContextObject", AdvancedDisplay="DepthPriority,bIsPersistent,Duration", DevelopmentOnly))
	static void DrawDebugFloatHistoryLocationEx(const UObject* WorldContextObject, const FTransform WorldTransform, const FDebugFloatHistory& FloatHistory=FDebugFloatHistory(), FVector Location=FVector::ZeroVector, FVector2D DrawSize=FVector2D::ZeroVector, FLinearColor DebugColor=FLinearColor::White, ESceneDepthPriority DepthPriority=Low, bool bIsPersistent=false, float Duration=0.f);
#pragma endregion Extended Native Drawing Methods

#pragma region New Drawing Methods
	/**
	* Extended Version
	* Draw a Debug Mesh Shape at Location
	*
	* @param WorldContextObject
	* @param StaticMesh				StaticMesh to use as base when drawing the wireframe shape
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Location				Location of the mesh shape
	* @param Rotation				Rotation of the mesh shape
	* @param LOD					LOD to use when calculating the edges, defaults to 0 if invalid
	* @param DebugColor				Color of the mesh shape in sRGB
	* @param DepthPriority			Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param bIsPersistent			Whether the histogram should persist after drawing once, call 'FlushPersistentDebugLines' to clean them up
	* @param Duration				How long the histogram will be drawn for in seconds, unrelated to 'bIsPersistent'
	* @param Thickness				Thickness of the drawn mesh shape
	*/
	UFUNCTION(BlueprintCallable, Category = "Rendering|Debug|Extended", meta=(WorldContext="WorldContextObject", AdvancedDisplay="DepthPriority,bIsPersistent,Duration,Thickness",DevelopmentOnly))
	static void DrawDebugMesh(const UObject* WorldContextObject, UStaticMesh* StaticMesh, const FTransform WorldTransform, FVector Location=FVector::ZeroVector, FRotator Rotation=FRotator::ZeroRotator, int32 LOD=0, FLinearColor DebugColor=FLinearColor::White, ESceneDepthPriority DepthPriority=Low, bool bIsPersistent=false, float Duration=0.f, float Thickness=1.f);
#pragma endregion New Drawing Methods

#pragma region Extended Native Trace Methods
	#pragma region Line Trace
	/**
	* Extended Version
	* Does a collision trace along the given line and returns the first blocking hit encountered.
	* This trace finds the objects that RESPONDS to the given TraceChannel
	* 
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the raycast
	* @param End					End location of the raycast
	* @param TraceChannel			The channel used to determine which components to hit against
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param DrawDebugType			Whether to and how to draw a debug line
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResult				Resulting properties of the raycast
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TraceThickness			Thickness of the drawn debug lines
	* @param TracePointSize			Size of the drawn debug point
	* @param TraceDrawTime			Duration in seconds at which to draw the debug lines. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category="Collision|Extended", meta=(bIgnoreSelf="true", WorldContext="WorldContextObject", AutoCreateRefTerm="ActorsToIgnore", DisplayName="Line Trace By Channel Ex", AdvancedDisplay="TraceDepthPriority,TraceThickness,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords="raycast,hitscan"))
	static bool LineTraceSingleEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, bool bTraceComplex, bool bIgnoreSelf, ETraceTypeQuery TraceChannel, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TraceThickness=0.f, float TracePointSize=16.f, float TraceDrawTime=5.0f);

	/**
	* Extended Version
	* Trace a ray against the world using a specific profile and return the first blocking hit
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the raycast
	* @param End					End location of the raycast
	* @param ProfileName			Name of the Collision Preset used to determine what to hit against
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param DrawDebugType			Whether to and how to draw a debug line
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResult				Resulting properties of the raycast
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TraceThickness			Thickness of the drawn debug lines
	* @param TracePointSize			Size of the drawn debug point
	* @param TraceDrawTime			Duration in seconds at which to draw the debug lines. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category = "Collision|Extended", meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", DisplayName = "Line Trace By Profile Ex", AdvancedDisplay = "TraceDepthPriority,TraceThickness,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords = "raycast,hitscan"))
	static bool LineTraceSingleByProfile(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, bool bTraceComplex, bool bIgnoreSelf, FName ProfileName, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TraceThickness=0.f, float TracePointSize=16.f, float TraceDrawTime=5.0f);
	
	/**
	* Extended Version
	* Does a collision trace along the given line and returns the first hit encountered.
	* This only finds objects that are of a type specified by ObjectTypes.
	* 
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the raycast
	* @param End					End location of the raycast
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param ObjectTypes			Array of Object Types to trace against
	* @param DrawDebugType			Whether to and how to draw a debug line
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResult				Resulting properties of the raycast
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TraceThickness			Thickness of the drawn debug lines
	* @param TracePointSize			Size of the drawn debug point
	* @param TraceDrawTime			Duration in seconds at which to draw the debug lines. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category="Collision|Extended", meta=(bIgnoreSelf="true", WorldContext="WorldContextObject", AutoCreateRefTerm="ActorsToIgnore", DisplayName = "Line Trace For Objects Ex", AdvancedDisplay="TraceDepthPriority,TraceThickness,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords="raycast,hitscan"))
	static bool LineTraceSingleForObjectsEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, bool bTraceComplex, bool bIgnoreSelf, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TraceThickness=0.f, float TracePointSize=16.f, float TraceDrawTime=5.f);
	#pragma endregion Line Trace

	#pragma region Multi Line Trace
	/**
	* Extended Version
	* Does a collision trace along the given line and returns all hits encountered up to and including the first blocking hit.
	* This trace finds the objects that RESPOND to the given TraceChannel
	* 
	* @param WorldContextObject		World context
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the raycast
	* @param End					End location of the raycast
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param TraceChannel			The channel to trace against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResults				Array of hit results
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TraceThickness			Thickness of the drawn debug lines
	* @param TracePointSize			Size of the drawn debug point
	* @param TraceDrawTime			Duration in seconds at which to draw the debug lines. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category="Collision|Extended", meta=(bIgnoreSelf="true", WorldContext="WorldContextObject", AutoCreateRefTerm="ActorsToIgnore", DisplayName = "Multi Line Trace By Channel Ex", AdvancedDisplay="TraceDepthPriority,TraceThickness,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords="raycast,hitscan"))
	static bool LineTraceMulti(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, bool bTraceComplex, bool bIgnoreSelf, ETraceTypeQuery TraceChannel, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TraceThickness=0.f, float TracePointSize=16.f, float TraceDrawTime=5.f);

	/**
	* Extended Version
	*  Trace a ray against the world using a specific profile and return overlapping hits and then first blocking hit
	*  Results are sorted, so a blocking hit (if found) will be the last element of the array
	*  Only the single closest blocking result will be generated, no tests will be done after that
	*
	* @param WorldContextObject		World context
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the raycast
	* @param End					End location of the raycast
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param ProfileName			Name of the Collision Preset used to determine what to hit against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResults				Array of hit results
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TraceThickness			Thickness of the drawn debug lines
	* @param TracePointSize			Size of the drawn debug point
	* @param TraceDrawTime			Duration in seconds at which to draw the debug lines. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category = "Collision|Extended", meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", DisplayName = "Multi Line Trace By Profile Ex", AdvancedDisplay = "TraceDepthPriority,TraceThickness,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords = "raycast,hitscan"))
	static bool LineTraceMultiByProfile(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, bool bTraceComplex, bool bIgnoreSelf, FName ProfileName, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TraceThickness=0.f, float TracePointSize=16.f, float TraceDrawTime=5.f);

	/**
	* Extended Version
	* Does a collision trace along the given line and returns all hits encountered.
	* This only finds objects that are of a type specified by ObjectTypes.
	* 
	* @param WorldContextObject		World context
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the raycast
	* @param End					End location of the raycast
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param ObjectTypes			Array of Object Types to trace against
	* @param ActorsToIgnore
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param HitResults				Array of hit results
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TraceThickness			Thickness of the drawn debug lines
	* @param TracePointSize			Size of the drawn debug point
	* @param TraceDrawTime			Duration in seconds at which to draw the debug lines. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category="Collision|Extended", meta=(bIgnoreSelf="true", WorldContext="WorldContextObject", AutoCreateRefTerm="ActorsToIgnore", DisplayName = "Multi Line Trace For Objects Ex", AdvancedDisplay="TraceDepthPriority,TraceThickness,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords="raycast,hitscan"))
	static bool LineTraceMultiForObjects(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, bool bTraceComplex, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TraceThickness=0.f, float TracePointSize=16.f, float TraceDrawTime=5.f);
	#pragma endregion Multi Line Trace

#pragma region Box Trace
	/**
	* Extended Version
	* Sweeps a box along the given line and returns the first blocking hit encountered.
	* This trace finds the objects that RESPONDS to the given TraceChannel
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param HalfSize				Distance from the center of box along each axis
	* @param Orientation			Orientation of the box
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param TraceChannel			The channel to trace against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResult				Resulting properties of the raycast
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the drawn debug point
	* @param TraceDrawTime			Duration in seconds at which to draw the debug lines. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Collision|Extended", meta = (bIgnoreSelf = "true", WorldContext="WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", DisplayName = "Box Trace By Channel Ex", AdvancedDisplay="TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords="raycast,hitscan,sweep"))
	static bool BoxTraceSingleEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, const FVector HalfSize, const FRotator Orientation, bool bTraceComplex, bool bIgnoreSelf, ETraceTypeQuery TraceChannel, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);

	/**
	* Extended Version
	* Sweep a box against the world and return the first blocking hit using a specific profile
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param HalfSize				Distance from the center of box along each axis
	* @param Orientation			Orientation of the box
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param ProfileName			Name of the Collision Preset used to determine what to hit against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResult				Resulting properties of the raycast
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the drawn debug point
	* @param TraceDrawTime			Duration in seconds at which to draw the debug lines. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Collision|Extended", meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", DisplayName = "Box Trace By Profile Ex", AdvancedDisplay = "TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords = "raycast,hitscan,sweep"))
	static bool BoxTraceSingleByProfileEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, const FVector HalfSize, const FRotator Orientation, bool bTraceComplex, bool bIgnoreSelf, FName ProfileName, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);

	/**
	* Extended Version
	* Sweeps a box along the given line and returns the first hit encountered.
	* This only finds objects that are of a type specified by ObjectTypes.
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param HalfSize				Distance from the center of box along each axis
	* @param Orientation			Orientation of the box
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param ObjectTypes			Array of Object Types to trace against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResult				Resulting properties of the raycast
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the drawn debug point
	* @param TraceDrawTime			Duration in seconds at which to draw the debug lines. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Collision|Extended", meta = (bIgnoreSelf = "true", WorldContext="WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", DisplayName = "Box Trace For Objects Ex", AdvancedDisplay="TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords="raycast,hitscan,sweep"))
	static bool BoxTraceSingleForObjectsEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, const FVector HalfSize, const FRotator Orientation, bool bTraceComplex, bool bIgnoreSelf, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);
#pragma endregion Box Trace

#pragma region Multi Box Trace
	/**
	* Extended Version
	* Sweeps a box along the given line and returns all hits encountered.
	* This trace finds the objects that RESPONDS to the given TraceChannel
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param HalfSize				Distance from the center of box along each axis
	* @param Orientation			Orientation of the box
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param TraceChannel			Array of Object Types to trace against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResults				Array of hit results
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the drawn debug point
	* @param TraceDrawTime			Duration in seconds at which to draw the debug lines. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category = "Collision|Extended", meta = (bIgnoreSelf = "true", WorldContext="WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", DisplayName = "Multi Box Trace By Channel Ex", AdvancedDisplay="TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords="raycast,hitscan,sweep"))
	static bool BoxTraceMultiEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, FVector HalfSize, const FRotator Orientation, bool bTraceComplex, bool bIgnoreSelf, ETraceTypeQuery TraceChannel, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);

	/**
	* Extended Version
	*  Sweep a box against the world and return all initial overlaps using a specific profile, then overlapping hits and then first blocking hit
	*  Results are sorted, so a blocking hit (if found) will be the last element of the array
	*  Only the single closest blocking result will be generated, no tests will be done after that
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param HalfSize				Distance from the center of box along each axis
	* @param Orientation			Orientation of the box
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param ProfileName			Name of the Collision Preset used to determine what to hit against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResults				Array of hit results
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the drawn debug point
	* @param TraceDrawTime			Duration in seconds at which to draw the debug lines. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category = "Collision|Extended", meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", DisplayName = "Multi Box Trace By Profile Ex", AdvancedDisplay = "TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords = "raycast,hitscan,sweep"))
	static bool BoxTraceMultiByProfileEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, FVector HalfSize, const FRotator Orientation, bool bTraceComplex, bool bIgnoreSelf, FName ProfileName, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);

	/**
	* Extended Version
	* Sweeps a box along the given line and returns all hits encountered.
	* This only finds objects that are of a type specified by ObjectTypes.
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param HalfSize				Distance from the center of box along each axis
	* @param Orientation			Orientation of the box
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param ObjectTypes			Array of Object Types to trace against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResults				Array of hit results
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the drawn debug point
	* @param TraceDrawTime			Duration in seconds at which to draw the debug lines. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category = "Collision|Extended", meta = (bIgnoreSelf = "true", WorldContext="WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", DisplayName = "Multi Box Trace For Objects Ex", AdvancedDisplay="TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords="raycast,hitscan,sweep"))
	static bool BoxTraceMultiForObjectsEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, const FVector HalfSize, const FRotator Orientation, bool bTraceComplex, bool bIgnoreSelf, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);
#pragma endregion Multi Box Trace

#pragma region Sphere Trace
	/**
	* Extended Version
	* Sweeps a sphere along the given line and returns the first blocking hit encountered.
	* This trace finds the objects that RESPONDS to the given TraceChannel
	* 
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param Radius					Radius of the sphere shape
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param TraceChannel			The channel to trace against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResult				Properties of the trace hit
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the point drawn at hit location
	* @param TraceDrawTime			Duration in seconds at which to draw the debug shape. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category="Collision|Extended", meta=(bIgnoreSelf="true", WorldContext="WorldContextObject", AutoCreateRefTerm="ActorsToIgnore", DisplayName = "Sphere Trace By Channel Ex", AdvancedDisplay="TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords="raycast,hitscan,sweep"))
	static bool SphereTraceSingleEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, bool bTraceComplex, bool bIgnoreSelf, ETraceTypeQuery TraceChannel, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);

	/**
	* Extended Version
	* Sweep a sphere against the world and return the first blocking hit using a specific profile
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param Radius					Radius of the sphere shape
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param ProfileName			The channel to trace against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResult				Properties of the trace hit
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the point drawn at hit location
	* @param TraceDrawTime			Duration in seconds at which to draw the debug shape. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category = "Collision|Extended", meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", DisplayName = "Sphere Trace By Profile Ex", AdvancedDisplay = "TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords = "raycast,hitscan,sweep"))
	static bool SphereTraceSingleByProfileEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, bool bTraceComplex, bool bIgnoreSelf, FName ProfileName, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);

	/**
	* Sweeps a sphere along the given line and returns the first hit encountered.
	* This only finds objects that are of a type specified by ObjectTypes.
	* 
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param Radius					Radius of the sphere shape
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param ObjectTypes			Array of Object Types to trace against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResult				Properties of the trace hit
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the point drawn at hit location
	* @param TraceDrawTime			Duration in seconds at which to draw the debug shape. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category="Collision|Extended", meta=(bIgnoreSelf="true", WorldContext="WorldContextObject", AutoCreateRefTerm="ActorsToIgnore", DisplayName = "Sphere Trace For Objects Ex", AdvancedDisplay="TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords="raycast,hitscan,sweep"))
	static bool SphereTraceSingleForObjectsEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, bool bTraceComplex, bool bIgnoreSelf, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);
#pragma endregion Sphere Trace
	
#pragma region Multi Sphere Trace
	/**
	* Extended Version
	* Sweeps a sphere along the given line and returns all hits encountered up to and including the first blocking hit.
	* This trace finds the objects that RESPOND to the given TraceChannel
	* 
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param Radius					Radius of the sphere shape
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param TraceChannel			The channel to trace against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResults				Array of hit results
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the point drawn at hit locations
	* @param TraceDrawTime			Duration in seconds at which to draw the debug shape. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category="Collision|Extended", meta=(bIgnoreSelf="true", WorldContext="WorldContextObject", AutoCreateRefTerm="ActorsToIgnore", DisplayName = "Multi Sphere Trace By Channel Ex", AdvancedDisplay="TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords="raycast,hitscan,sweep"))
	static bool SphereTraceMultiEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, bool bTraceComplex, bool bIgnoreSelf, ETraceTypeQuery TraceChannel, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);

	/**
	* Extended Version
	* Sweep a sphere against the world and return all initial overlaps using a specific profile, then overlapping hits and then first blocking hit
	* Results are sorted, so a blocking hit (if found) will be the last element of the array
	* Only the single closest blocking result will be generated, no tests will be done after that
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param Radius					Radius of the sphere shape
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param ProfileName			Name of the Collision Preset used to determine what to hit against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResults				Array of hit results
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the point drawn at hit locations
	* @param TraceDrawTime			Duration in seconds at which to draw the debug shape. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category = "Collision|Extended", meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", DisplayName = "Multi Sphere Trace By Profile Ex", AdvancedDisplay = "TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords = "raycast,hitscan,sweep"))
	static bool SphereTraceMultiByProfileEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, bool bTraceComplex, bool bIgnoreSelf, FName ProfileName, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);

	/**
	* Extended Version
	* Sweeps a sphere along the given line and returns all hits encountered.
	* This only finds objects that are of a type specified by ObjectTypes.
	* 
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param Radius					Radius of the sphere shape
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param ObjectTypes			Array of Object Types to trace against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResults				Array of hit results
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the point drawn at hit location
	* @param TraceDrawTime			Duration in seconds at which to draw the debug shape. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category="Collision|Extended", meta=(bIgnoreSelf="true", WorldContext="WorldContextObject", AutoCreateRefTerm="ActorsToIgnore", DisplayName = "Multi Sphere Trace For Objects Ex", AdvancedDisplay="TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords="raycast,hitscan,sweep"))
	static bool SphereTraceMultiForObjectsEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, bool bTraceComplex, bool bIgnoreSelf, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);
#pragma endregion  Multi Sphere Trace

#pragma region Capsule Trace
	/**
	* Extended Version
	* Sweeps a capsule along the given line and returns the first blocking hit encountered.
	* This trace finds the objects that RESPOND to the given TraceChannel
	* 
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param Radius					Radius of the capsule shape
	* @param HalfHeight				Half-height of the debug shape
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param TraceChannel			The channel to trace against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResult				Properties of the trace hit
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the point drawn at hit location
	* @param TraceDrawTime			Duration in seconds at which to draw the debug shape. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category="Collision|Extended", meta=(bIgnoreSelf="true", WorldContext="WorldContextObject", AutoCreateRefTerm="ActorsToIgnore", DisplayName = "Capsule Trace By Channel Ex", AdvancedDisplay="TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords="raycast,hitscan,sweep"))
	static bool CapsuleTraceSingleEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, float HalfHeight, bool bTraceComplex, bool bIgnoreSelf, ETraceTypeQuery TraceChannel, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);

	/**
	* Extended Version
	* Sweep a capsule against the world and return the first blocking hit using a specific profile
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param Radius					Radius of the capsule shape
	* @param HalfHeight				Half-height of the debug shape
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param ProfileName			Name of the Collision Preset used to determine what to hit against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResult				Properties of the trace hit
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the point drawn at hit location
	* @param TraceDrawTime			Duration in seconds at which to draw the debug shape. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category = "Collision|Extended", meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", DisplayName = "Capsule Trace By Profile Ex", AdvancedDisplay = "TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords = "raycast,hitscan,sweep"))
	static bool CapsuleTraceSingleByProfileEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, float HalfHeight, bool bTraceComplex, bool bIgnoreSelf, FName ProfileName, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);

	/**
	* Extended Version
	* Sweeps a capsule along the given line and returns the first hit encountered.
	* This only finds objects that are of a type specified by ObjectTypes.
	* 
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param Radius					Radius of the capsule shape
	* @param HalfHeight				Half-height of the debug shape
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param ObjectTypes			Array of Object Types to trace against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResult				Properties of the trace hit
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the point drawn at hit location
	* @param TraceDrawTime			Duration in seconds at which to draw the debug shape. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category="Collision|Extended", meta=(bIgnoreSelf="true", WorldContext="WorldContextObject", AutoCreateRefTerm="ActorsToIgnore", DisplayName = "Capsule Trace For Objects Ex", AdvancedDisplay="TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords="raycast,hitscan,sweep"))
	static bool CapsuleTraceSingleForObjectsEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, float HalfHeight, bool bTraceComplex, bool bIgnoreSelf, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, FHitResult& HitResult, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);
#pragma endregion Capsule Trace

#pragma region Multi Capsule Trace
	/**
	* Extended Version
	* Sweeps a capsule along the given line and returns all hits encountered up to and including the first blocking hit.
	* This trace finds the objects that RESPOND to the given TraceChannel
	* 
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param Radius					Radius of the capsule shape
	* @param HalfHeight				Half-height of the debug shape
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param TraceChannel			The channel to trace against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResults				Array of hit results
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the point drawn at hit location
	* @param TraceDrawTime			Duration in seconds at which to draw the debug shape. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category="Collision|Extended", meta=(bIgnoreSelf="true", WorldContext="WorldContextObject", AutoCreateRefTerm="ActorsToIgnore", DisplayName = "Multi Capsule Trace By Channel Ex", AdvancedDisplay="TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords="raycast,hitscan,sweep"))
	static bool CapsuleTraceMultiEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, float HalfHeight, bool bTraceComplex, bool bIgnoreSelf, ETraceTypeQuery TraceChannel, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);

	/**
	* Extended Version
	*  Sweep a capsule against the world and return all initial overlaps using a specific profile, then overlapping hits and then first blocking hit
	*  Results are sorted, so a blocking hit (if found) will be the last element of the array
	*  Only the single closest blocking result will be generated, no tests will be done after that
	*
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param Radius					Radius of the capsule shape
	* @param HalfHeight				Half-height of the debug shape
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param ProfileName			Name of the Collision Preset used to determine what to hit against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResults				Array of hit results
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the point drawn at hit location
	* @param TraceDrawTime			Duration in seconds at which to draw the debug shape. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category = "Collision|Extended", meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", DisplayName = "Multi Capsule Trace By Profile Ex", AdvancedDisplay = "TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords = "raycast,hitscan,sweep"))
	static bool CapsuleTraceMultiByProfileEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, float HalfHeight, bool bTraceComplex, bool bIgnoreSelf, FName ProfileName, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);

	/**
	* Extended Version
	* Sweeps a capsule along the given line and returns all hits encountered.
	* This only finds objects that are of a type specified by ObjectTypes.
	* 
	* @param WorldContextObject
	* @param WorldTransform			Start and End will be local to this transform. If undefined, Start and End locations will be world-based
	* @param Start					Start location of the sweep test
	* @param End					End location of the sweep test
	* @param Radius					Radius of the capsule shape
	* @param HalfHeight				Half-height of the debug shape
	* @param bTraceComplex			True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf			True to ignore tracing against the actor from which this was called
	* @param ObjectTypes			Array of Object Types to trace against
	* @param DrawDebugType			Whether to and how to draw a debug shape
	* @param ActorsToIgnore			Array of actors to not hit against
	* @param HitResults				Array of hit results
	* @param TraceDepthPriority		Depth priority when drawing, 'Medium' renders on top of basic geometry
	* @param TraceColor
	* @param TraceHitColor
	* @param TracePointSize			Size of the point drawn at hit location
	* @param TraceDrawTime			Duration in seconds at which to draw the debug shape. Only works with 'ForDuration' debug type
	* @return						True if there was a hit, false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category="Collision|Extended", meta=(bIgnoreSelf="true", WorldContext="WorldContextObject", AutoCreateRefTerm="ActorsToIgnore", DisplayName = "Multi Capsule Trace For Objects Ex", AdvancedDisplay="TraceDepthPriority,TracePointSize,TraceColor,TraceHitColor,TraceDrawTime", Keywords="raycast,hitscan,sweep"))
	static bool CapsuleTraceMultiForObjectsEx(const UObject* WorldContextObject, const FTransform WorldTransform, FVector Start, FVector End, float Radius, float HalfHeight, bool bTraceComplex, bool bIgnoreSelf, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, EDrawDebugTrace::Type DrawDebugType, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& HitResults, ESceneDepthPriority TraceDepthPriority=Low, FLinearColor TraceColor=FLinearColor::Red, FLinearColor TraceHitColor=FLinearColor::Green, float TracePointSize=16.f, float TraceDrawTime=5.f);
#pragma endregion  Multi Capsule Trace
#pragma endregion Extended Native Trace Methods

	// Extended Version of 'LogString'. CategoryName can be used as a filter after having been used once, will go away after editor restart
	/**
	* 
	* @param WorldContextObject
	* @param InString The string to log
	* @param CategoryName The category name, None will use 'LogBlueprintUserMessages' as default
	* @param Verbosity The verbosity of the log message
	*/
	UFUNCTION(BlueprintCallable, Category="Utilities|String|Extended", meta=(BlueprintThreadSafe, WorldContext="WorldContextObject", Keywords = "log,print", DevelopmentOnly))
	static void LogStringEx(const UObject* WorldContextObject, const FString& InString=FString(TEXT("Hello")), FName CategoryName=NAME_None, TEnumAsByte<ELogVerbosityEx> Verbosity=Log);

	/**
	 * Prints a string to the log, and optionally, to the screen
	 * If Print To Log is true, it will be visible in the Output Log window.  Otherwise it will be logged only as 'Verbose', so it generally won't show up.
	 *
	 * @param	InString			The string to log out
	 * @param	bPrintToScreen		Whether or not to print the output to the screen
	 * @param	bPrintToLog			Whether or not to print the output to the log
	 * @param	bPrintToConsole		Whether or not to print the output to the console
	 * @param	bNewerOnTop			Whether to print new entries at the top or bottom
	 * @param	TextColor			The color of the text to display
	 * @param	Duration			The display duration (if Print to Screen is True). Using negative number will result in loading the duration time from the config
	 * @param	Key					If a non-empty key is provided, the message will replace any existing on-screen messages with the same key
	 * @param	TextScale			Scale of the printed text (if Print to Screen is True)
	 */
	UFUNCTION(BlueprintCallable, Category="Development|Extended", meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "2", DevelopmentOnly))
	static void PrintStringEx(const UObject* WorldContextObject, const FString& InString=FString(TEXT("Hello")), bool bPrintToScreen=true, bool bPrintToLog=true, bool bPrintToConsole=false, bool bNewerOnTop=true, FLinearColor TextColor=FLinearColor(0.0, 0.66, 1.0), float Duration=2.f, const FName Key=NAME_None, const FVector2D TextScale=FVector2D(1.0, 1.0));
};
