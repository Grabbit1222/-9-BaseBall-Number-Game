#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BaseBallGameState.generated.h"

class ABaseBallPlayerController;

UENUM(BlueprintType)
enum class EPlayerTurn : uint8
{
    None UMETA(DisplayName = "None"),
    Host UMETA(DisplayName = "Host"),
    Guest UMETA(DisplayName = "Guest")
};


UCLASS()
class BASEBALLGAME_API ABaseBallGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    ABaseBallGameState();

    UPROPERTY(Replicated)
    int PlayerCount = 0;
    UPROPERTY(Replicated)
    EPlayerTurn CurrentTurn = EPlayerTurn::Host; // 현재 턴
    UPROPERTY()
    TArray<FString> ChatMessages;
    UPROPERTY(Replicated)
    int HostAttempts = 0;
    UPROPERTY(Replicated)
    int GuestAttempts = 0;

    UFUNCTION(NetMulticast, Reliable)
    void MulticastOnChatMessageReceived(const FString& Message);
    void MulticastOnChatMessageReceived_Implementation(const FString& Message);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_PlayerCountChanged(int NewPlayerCount);  // 플레이어 수 변경 시 호출
    void Multicast_PlayerCountChanged_Implementation(int NewPlayerCount);

    EPlayerTurn GetCurrentTurn() const { return CurrentTurn; }
    EPlayerTurn AssignPlayerTurn(ABaseBallPlayerController* Controller);
    void AddGameProgressMessage(const FString& Message);
    void ServerAddChatMessage(ABaseBallPlayerController* Player, const FString& Message);
    void ProcessPlayerTurn(ABaseBallPlayerController* Player, const FString& Message);
    void ResetAttempts();
   
protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
    ABaseBallPlayerController* HostController = nullptr;
    ABaseBallPlayerController* GuestController = nullptr;
    void IncreaseTurnCount(EPlayerTurn Turn);

};
