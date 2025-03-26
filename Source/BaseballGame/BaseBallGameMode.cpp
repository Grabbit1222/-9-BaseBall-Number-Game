#include "BaseBallGameMode.h"
#include "BaseBallGameState.h"
#include "BaseBallLogic.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

ABaseBallGameMode::ABaseBallGameMode()
{
    bReplicates = false;
}

void ABaseBallGameMode::BeginPlay()
{
    Super::BeginPlay();

}

void ABaseBallGameMode::StartNewGame()
{
    TargetNumber = GenerateRandomNumber();

    ABaseBallGameState* MyGameState = GetWorld()->GetGameState<ABaseBallGameState>();
    if (MyGameState)
    {
        MyGameState->AddGameProgressMessage("BaseBall Number Game Start!");
        MyGameState->AddGameProgressMessage("Type in 3 distinct numbers after slash(/)");
		MyGameState->AddGameProgressMessage("Current Random Number: " + TargetNumber);
		MyGameState->ResetAttempts();
    }
}

FString ABaseBallGameMode::GenerateRandomNumber()
{
    return UBaseBallLogic::GenerateUniqueRandomNumber();
}

void ABaseBallGameMode::ProcessPlayerGuess(APlayerController* Player, const FString& Input)
{
    FString Guess = Input.Mid(1);
    int32 Strikes = 0, Balls = 0;
    UBaseBallLogic::CalculateScore(TargetNumber, Guess, Strikes, Balls);

    ABaseBallGameState* MyGameState = GetWorld()->GetGameState<ABaseBallGameState>();
    if (MyGameState)
    {
        MyGameState->AddGameProgressMessage(FString::Printf(TEXT("Input: %s, Result: %dS %dB"), *Guess, Strikes, Balls));

        if (Strikes == 3)
        {
            MyGameState->AddGameProgressMessage(TEXT("3 Strikes! Game Over. Starting a new game..."));
            StartNewGame();
        }
    }
}


void ABaseBallGameMode::HandleGameDraw()
{
    ABaseBallGameState* MyGameState = GetWorld()->GetGameState<ABaseBallGameState>();
    if (MyGameState)
    {
        MyGameState->AddGameProgressMessage(TEXT("It's a draw. A new game has started."));
    }
    StartNewGame();
}
