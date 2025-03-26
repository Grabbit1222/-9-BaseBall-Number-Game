#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlateCore.h"
#include "ChatWidget.generated.h"

UCLASS()
class BASEBALLGAME_API UChatWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /** 블루프린트에서 메시지를 추가할 수 있도록 UFUNCTION 설정 */
    UFUNCTION(BlueprintCallable, Category = "Chat")
    void AddChatMessage(const FString& Message);

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    class UEditableText* ChatInputBox;
    UPROPERTY(meta = (BindWidget))
    class UScrollBox* ChatScrollBox;
    UPROPERTY(EditAnywhere, Category = "Chat")
    TSubclassOf<class UUserWidget> ChatMessageClass;

    UFUNCTION()
    void OnTextCommittedHandler(const FText& Text, ETextCommit::Type CommitMethod);
};