// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

UCLASS()
class SIDEDENEME_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext, Keywords = "log print"), Category="MyBlueprintFunctionLibrary")
	static void QuickPrint(const UObject* WorldContextObject, const FString& Append = FString(TEXT("")),const FString& InString = FString(TEXT("Hello")), bool bPrintToScreen = true, const FLinearColor TextColor = FLinearColor(0.0, 0.66, 1.0), float Duration = 2.f);

	/** Returns the local player controller at the specified player index */
	UFUNCTION(BlueprintPure, Category="Game", meta=(WorldContext="WorldContextObject", UnsafeDuringActorConstruction="true"))
	static APlayerController* GetLocalPlayerController(const UObject* WorldContextObject, int32 PlayerIndex);
};
