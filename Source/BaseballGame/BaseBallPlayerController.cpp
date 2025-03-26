#include "BaseBallPlayerController.h"
#include "BaseBallGameState.h"
#include "ChatWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ABaseBallPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Log, TEXT("BeginPlay called. Initializing ChatWidget"));

    InitializeChatWidget(); // ���� �ʱ�ȭ
}

void ABaseBallPlayerController::InitializeChatWidget()
{
    if (GetRemoteRole() != ROLE_None && !PlayerChatWidget)
    {
        TArray<UUserWidget*> FoundWidgets;
        UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UChatWidget::StaticClass(), true);  // true -> Only top-level widgets

        if (FoundWidgets.Num() > 0)
        {
            PlayerChatWidget = Cast<UChatWidget>(FoundWidgets[0]);
            if (PlayerChatWidget)
            {
				ServerCountPlayers();
            }
        }
    }
}


void ABaseBallPlayerController::OnChatMessageReceived(const FString& Message)
{
    if (PlayerChatWidget)
    {
        PlayerChatWidget->AddChatMessage(Message); // Update UI
    }
}

void ABaseBallPlayerController::ServerSendChatMessage_Implementation(const FString& Message)
{
    ABaseBallGameState* GameState = GetWorld()->GetGameState<ABaseBallGameState>();
    if (GameState)
    {
        GameState->ServerAddChatMessage(this, Message);

        if (Message.StartsWith(TEXT("/")))
        {
            if (GameState->GetCurrentTurn() == PlayerTurn)
            {
                GameState->ProcessPlayerTurn(this, Message);
            }
            else
            {
                FString TurnMessage = (GameState->GetCurrentTurn() == EPlayerTurn::Host)
                    ? TEXT("It's Host's Turn!")
                    : TEXT("It's Guest's Turn!");

                GameState->ServerAddChatMessage(this, TurnMessage);
            }
        }
    }
}

void ABaseBallPlayerController::ServerCountPlayers_Implementation()
{
	ABaseBallGameState* GameState = GetWorld()->GetGameState<ABaseBallGameState>();
	if (GameState)
	{
        GameState->Multicast_PlayerCountChanged(1);
        PlayerTurn = GameState->AssignPlayerTurn(this); // �÷��̾� �� �Ҵ�
	}
}


void ABaseBallPlayerController::OnGameProgressUpdated(const FString& Message)
{
    if (PlayerChatWidget)
    {
        PlayerChatWidget->AddChatMessage(Message); // ���� ���� ��Ȳ�� UI�� �ݿ�
    }
}
