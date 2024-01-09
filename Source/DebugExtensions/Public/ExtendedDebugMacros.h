// Copyright 2023 'Dealman' - All Rights Reserved

#pragma once

// START EXTENDED MACROS

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) || USE_LOGGING_IN_SHIPPING
/** Displays a on-screen debug message with a CUSTOM color
 * 
 * @param Text Message to display on screen
 * @param Key Unique identifier, updates previous message if it already exists. Prevents 'spam'
 * @param Duration Duration in seconds to display the message
 * @param Color Custom color of the message (FColor)
 */
#define UE_SCREENMESSAGE_CUSTOM_EX(Text, Key, Duration, Color) if(GEngine){GEngine->AddOnScreenDebugMessage(Key, Duration, Color, FString::Printf(TEXT(Text)));}
/** Displays a CYAN on-screen debug message
 * 
 * @param Text Message to display on screen
 * @param Key Unique identifier, updates previous message if it already exists. Prevents 'spam'
 * @param Duration Duration in seconds to display the message
 */
#define UE_SCREENMESSAGE_EX(Text, Key, Duration) if(GEngine){GEngine->AddOnScreenDebugMessage(Key, Duration, FColor::Cyan, FString::Printf(TEXT(Text)));}
/** Displays a RED on-screen debug message
 * 
 * @param Text Message to display on screen
 * @param Key Unique identifier, updates previous message if it already exists. Prevents 'spam'
 * @param Duration Duration in seconds to display the message
 */
#define UE_SCREENMESSAGE_ERROR_EX(Text, Key, Duration) if(GEngine){GEngine->AddOnScreenDebugMessage(Key, Duration, FColor::Red, FString::Printf(TEXT(Text)));}
/** Displays a YELLOW on-screen debug message
 * 
 * @param Text(string) Message to display on screen
 * @param Key(int32) Unique identifier, updates previous message if it already exists. Prevents 'spam'
 * @param Duration(double) Duration in seconds to display the message
 */
#define UE_SCREENMESSAGE_WARNING_EX(Text, Key, Duration) if(GEngine){GEngine->AddOnScreenDebugMessage(Key, Duration, FColor::Yellow, FString::Printf(TEXT(Text)));}
/** Displays a GREEN on-screen debug message
 * 
 * @param Text Message to display on screen
 * @param Key Unique identifier, updates previous message if it already exists. Prevents 'spam'
 * @param Duration Duration in seconds to display the message
 */
#define UE_SCREENMESSAGE_SUCCESS_EX(Text, Key, Duration) if(GEngine){GEngine->AddOnScreenDebugMessage(Key, Duration, FColor::Green, FString::Printf(TEXT(Text)));}
/** Displays a WHITE on-screen debug message
 * 
 * @param Text Message to display on screen
 * @param Key Unique identifier, updates previous message if it already exists. Prevents 'spam'
 * @param Duration Duration in seconds to display the message
 */
#define UE_SCREENMESSAGE_TEMP_EX(Text, Key, Duration) if(GEngine){GEngine->AddOnScreenDebugMessage(Key, Duration, FColor::White, FString::Printf(TEXT(Text)));}

// END EXTENDED MACROS

/** Displays a on-screen debug message with a CUSTOM color
 * 
 * @param Text Message to display on screen
 * @param Key Unique identifier, updates previous message if it already exists. Prevents 'spam'
 * @param Duration Duration in seconds to display the message
 * @param Color Custom color of the message (FColor)
 */
#define UE_SCREENMESSAGE_CUSTOM(Text, Color) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0, Color, FString::Printf(TEXT(Text)));}
/** Displays a CYAN on-screen debug message
 * 
 * @param Text Message to display on screen
 * @param Key Unique identifier, updates previous message if it already exists. Prevents 'spam'
 * @param Duration Duration in seconds to display the message
 */
#define UE_SCREENMESSAGE(Text) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0, FColor::Cyan, FString::Printf(TEXT(Text)));}
/** Displays a RED on-screen debug message
 * 
 * @param Text Message to display on screen
 * @param Key Unique identifier, updates previous message if it already exists. Prevents 'spam'
 * @param Duration Duration in seconds to display the message
 */
#define UE_SCREENMESSAGE_ERROR(Text) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0, FColor::Red, FString::Printf(TEXT(Text)));}
/** Displays a YELLOW on-screen debug message
 * 
 * @param Text(string) Message to display on screen
 * @param Key(int32) Unique identifier, updates previous message if it already exists. Prevents 'spam'
 * @param Duration(double) Duration in seconds to display the message
 */
#define UE_SCREENMESSAGE_WARNING(Text) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0, FColor::Yellow, FString::Printf(TEXT(Text)));}
/** Displays a GREEN on-screen debug message
 * 
 * @param Text Message to display on screen
 * @param Key Unique identifier, updates previous message if it already exists. Prevents 'spam'
 * @param Duration Duration in seconds to display the message
 */
#define UE_SCREENMESSAGE_SUCCESS(Text) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0, FColor::Green, FString::Printf(TEXT(Text)));}
/** Displays a WHITE on-screen debug message
 * 
 * @param Text Message to display on screen
 * @param Key Unique identifier, updates previous message if it already exists. Prevents 'spam'
 * @param Duration Duration in seconds to display the message
 */
#define UE_SCREENMESSAGE_TEMP(Text) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0, FColor::White, FString::Printf(TEXT(Text)));}
#endif
