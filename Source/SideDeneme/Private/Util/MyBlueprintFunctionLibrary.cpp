// Fill out your copyright notice in the Description page of Project Settings.

#include "Util/MyBlueprintFunctionLibrary.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/Console.h"
#include "Kismet/GameplayStatics.h"

void UMyBlueprintFunctionLibrary::QuickPrint(const UObject* WorldContextObject, const FString& Append,
                                             const FString& InString, bool bPrintToScreen, const FLinearColor TextColor, float Duration)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	FString Prefix;
	if (World)
	{
		if (World->WorldType == EWorldType::PIE)
		{
			switch (World->GetNetMode())
			{
			case NM_Client:
				// GPlayInEditorID 0 is always the server, so 1 will be first client.
				// You want to keep this logic in sync with GeneratePIEViewportWindowTitle and UpdatePlayInEditorWorldDebugString
				Prefix = FString::Printf(TEXT("Client %d: "), GPlayInEditorID);
				break;
			case NM_DedicatedServer:
			case NM_ListenServer:
				Prefix = FString::Printf(TEXT("Server: "));
				break;
			case NM_Standalone:
				break;
			}
		}
	}

	FString FinalDisplayString = "";
	if (Append.IsEmpty())
	{
		FinalDisplayString = Prefix + InString;
	} else
	{
		FinalDisplayString = Prefix + Append + ": " + InString;
	}
	
	FString FinalLogString = FinalDisplayString;

	static const FBoolConfigValueHelper DisplayPrintStringSource(
		TEXT("Kismet"), TEXT("bLogPrintStringSource"), GEngineIni);
	if (DisplayPrintStringSource)
	{
		const FString SourceObjectPrefix = FString::Printf(TEXT("[%s] "), *GetNameSafe(WorldContextObject));
		FinalLogString = SourceObjectPrefix + FinalLogString;
	}

	// Output to the screen, if possible
	if (bPrintToScreen)
	{
		if (GAreScreenMessagesEnabled)
		{
			if (GConfig && Duration < 0)
			{
				GConfig->GetFloat(TEXT("Kismet"), TEXT("PrintStringDuration"), Duration, GEngineIni);
			}
			GEngine->AddOnScreenDebugMessage((uint64)-1, Duration, TextColor.ToFColor(true), FinalDisplayString);
		}
		else
		{
			UE_LOG(LogBlueprint, VeryVerbose,
			       TEXT("Screen messages disabled (!GAreScreenMessagesEnabled).  Cannot print to screen."));
		}
	}
}

APlayerController* UMyBlueprintFunctionLibrary::GetLocalPlayerController(const UObject* WorldContextObject, int32 PlayerIndex ) 
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		uint32 Index = 0;
		for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APlayerController* PlayerController = Iterator->Get();
			if (Index == PlayerIndex)
			{
				if (PlayerController->IsLocalPlayerController())
				{
					return PlayerController;
				}
			}
			Index++;
		}
	}
	return nullptr;
}
