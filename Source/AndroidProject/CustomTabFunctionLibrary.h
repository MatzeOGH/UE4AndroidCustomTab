// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomTabFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ANDROIDPROJECT_API UCustomTabFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	/** Opens a custom Tab on Android, fallback to native launch url on all other platforms */ 
	UFUNCTION(BlueprintCallable)
	static void OpenCustomTab(const FString& Url);
	
};
