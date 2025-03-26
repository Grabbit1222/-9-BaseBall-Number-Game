#include "ChatWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "ChatMessageWidget.h"
#include "Components/EditableText.h"
#include "BaseBallPlayerController.h"

void UChatWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (ChatInputBox)
    {
        ChatInputBox->OnTextCommitted.AddDynamic(this, &UChatWidget::OnTextCommittedHandler);
    }
}


// 货肺款 皋矫瘤 困连 积己
void UChatWidget::AddChatMessage(const FString& Message)
{
    if (!ChatScrollBox || !ChatMessageClass) return;

    UChatMessageWidget* NewMessage = CreateWidget<UChatMessageWidget>(this, ChatMessageClass);
    if (NewMessage)
    {
        NewMessage->SetMessageText(Message);
        ChatScrollBox->AddChild(NewMessage);

		ChatScrollBox->ScrollToEnd();
    }
}

void UChatWidget::OnTextCommittedHandler(const FText& Text, ETextCommit::Type CommitMethod)
{
    if (CommitMethod == ETextCommit::OnEnter)
    {
        FString Message = Text.ToString();
        if (!Message.IsEmpty())
        {
            ABaseBallPlayerController* PlayerController = Cast<ABaseBallPlayerController>(GetOwningPlayer());
            if (PlayerController)
            {
                PlayerController->ServerSendChatMessage(Message);
            }

            ChatInputBox->SetText(FText::GetEmpty());
        }
    }
}