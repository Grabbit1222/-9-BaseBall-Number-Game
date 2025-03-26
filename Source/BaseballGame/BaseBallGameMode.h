#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseBallGameMode.generated.h"

UCLASS()
class BASEBALLGAME_API ABaseBallGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ABaseBallGameMode();

    UFUNCTION(BlueprintCallable, Category = "Game Logic")
    void ProcessPlayerGuess(APlayerController* Player, const FString& Input);
    UFUNCTION()
    void HandleGameDraw(); // ���º� ó�� �Լ�

    void StartNewGame();

protected:
    


    virtual void BeginPlay() override;

private:
    FString GenerateRandomNumber();

    FString TargetNumber; // �������� ������ ���� ����
};

