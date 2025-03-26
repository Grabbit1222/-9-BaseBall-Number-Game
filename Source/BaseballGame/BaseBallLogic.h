#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BaseBallLogic.generated.h"

UCLASS()
class BASEBALLGAME_API UBaseBallLogic : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FString GenerateUniqueRandomNumber();
	static bool IsValidInput(const FString& Input);
	static void CalculateScore(const FString& Target, const FString& Guess, int32& Strikes, int32& Balls);
};
