// Copyright 2023 'Dealman' - All Rights Reserved

#pragma once

/**
 * 
 * @param Text The message text
 * @param Key Unique identifier, updates text if it already exists
 * @param Duration Duration in seconds to display the message
 */
#define UE_DEBUGMESSAGE(Text, Key, Duration, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(Key, Duration, FColor::Cyan, FString::Printf(TEXT(Text), __VA_ARGS__));}
#define UE_DEBUGMESSAGE_ERROR(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}
#define UE_DEBUGMESSAGE_WARNING(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(x), __VA_ARGS__));}
#define UE_DEBUGMESSAGE_SUCCESS(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT(x), __VA_ARGS__));}
#define UE_DEBUGMESSAGE_TEMP(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT(x), __VA_ARGS__));}
