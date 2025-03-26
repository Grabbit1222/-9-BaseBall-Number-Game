#include "ChatMessageWidget.h"
#include "Components/TextBlock.h"

void UChatMessageWidget::SetMessageText(const FString& NewMessage)
{
    if (MessageText)
    {
        MessageText->SetText(FText::FromString(NewMessage));
    }
}