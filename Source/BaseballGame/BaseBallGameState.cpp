#include "BaseBallGameState.h"
#include "BaseBallGameMode.h"
#include "Net/UnrealNetwork.h"
#include "BaseBallPlayerController.h"
#include "BaseBallLogic.h"

ABaseBallGameState::ABaseBallGameState()
{
    bReplicates = true;
    bAlwaysRelevant = true;
}

void ABaseBallGameState::ServerAddChatMessage(ABaseBallPlayerController* Player, const FString& Message)
{
    if (Message.IsEmpty()) return;

    ChatMessages.Add(Message);
    MulticastOnChatMessageReceived(Message);
}

void ABaseBallGameState::AddGameProgressMessage(const FString& Message)
{
    MulticastOnChatMessageReceived(Message);
}

void ABaseBallGameState::MulticastOnChatMessageReceived_Implementation(const FString& Message)
{
    // 모든 클라이언트에서 메시지를 UI에 반영
    ABaseBallPlayerController* LocalBPC = Cast<ABaseBallPlayerController>(GetWorld()->GetFirstPlayerController());

    if (LocalBPC)
    {
        LocalBPC->OnChatMessageReceived(Message); // UI 업데이트
    }
}

void ABaseBallGameState::Multicast_PlayerCountChanged_Implementation(int Count)
{
    PlayerCount = PlayerCount + Count;

    ABaseBallPlayerController* LocalBPC = Cast<ABaseBallPlayerController>(GetWorld()->GetFirstPlayerController());

    if (LocalBPC)
    {
        FString Message = FString::Printf(TEXT("Current Player: %d"), PlayerCount);
        LocalBPC->OnChatMessageReceived(Message);

        ABaseBallGameMode* GameMode = Cast<ABaseBallGameMode>(GetWorld()->GetAuthGameMode());
        if (GameMode && PlayerCount == 2)
        {
            GameMode->StartNewGame();
        }
    }
}

EPlayerTurn ABaseBallGameState::AssignPlayerTurn(ABaseBallPlayerController* Controller)
{
    if (HostController == nullptr)
    {
        HostController = Controller;
        return EPlayerTurn::Host;
    }
    else if (GuestController == nullptr)
    {
        GuestController = Controller;
        return EPlayerTurn::Guest;
    }
    return EPlayerTurn::None;
}

void ABaseBallGameState::IncreaseTurnCount(EPlayerTurn Turn)
{
    if (Turn == EPlayerTurn::Host)
    {
        HostAttempts++;
    }
    else if (Turn == EPlayerTurn::Guest)
    {
        GuestAttempts++;
    }

    if (HostAttempts >= 3 && GuestAttempts >= 3)
    {
        ABaseBallGameMode* GameMode = Cast<ABaseBallGameMode>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->HandleGameDraw();
        }
    }
}


void ABaseBallGameState::ProcessPlayerTurn(ABaseBallPlayerController* Player, const FString& Message)
{
    if (UBaseBallLogic::IsValidInput(Message))
    {
        
        ABaseBallGameMode* GameMode = Cast<ABaseBallGameMode>(GetWorld()->GetAuthGameMode());
        GameMode->ProcessPlayerGuess(Player, Message);
    }

    IncreaseTurnCount(CurrentTurn);
    CurrentTurn = (CurrentTurn == EPlayerTurn::Host) ? EPlayerTurn::Guest : EPlayerTurn::Host; //Switch Turn
}

void ABaseBallGameState::ResetAttempts()
{
	HostAttempts = 0;
	GuestAttempts = 0;
}

void ABaseBallGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ABaseBallGameState, CurrentTurn);
    DOREPLIFETIME(ABaseBallGameState, PlayerCount);
    DOREPLIFETIME(ABaseBallGameState, HostAttempts);
	DOREPLIFETIME(ABaseBallGameState, GuestAttempts);
}

