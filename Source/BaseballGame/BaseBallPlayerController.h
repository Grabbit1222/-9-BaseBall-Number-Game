#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseBallGameState.h"
#include "BaseBallPlayerController.generated.h"

class UChatWidget;

UCLASS()
class BASEBALLGAME_API ABaseBallPlayerController : public APlayerController
{
    GENERATED_BODY()

public:


    UFUNCTION(Server, Reliable, WithValidation)
    void ServerSendChatMessage(const FString& Message);
    void ServerSendChatMessage_Implementation(const FString& Message);
    bool ServerSendChatMessage_Validate(const FString& Message) { return true; }
    UFUNCTION(Server, Reliable, WithValidation)
    void ServerCountPlayers();
    void ServerCountPlayers_Implementation();
    bool ServerCountPlayers_Validate() { return true; }

	void OnChatMessageReceived(const FString& Message);
    void OnGameProgressUpdated(const FString& Message);
    virtual void BeginPlay() override;

private:
    UChatWidget* PlayerChatWidget;
    void InitializeChatWidget();
    EPlayerTurn PlayerTurn = EPlayerTurn::None;
};


