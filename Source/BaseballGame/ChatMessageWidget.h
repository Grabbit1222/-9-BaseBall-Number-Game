#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatMessageWidget.generated.h"

UCLASS()
class BASEBALLGAME_API UChatMessageWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Chat")
	void SetMessageText(const FString& NewMessage);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MessageText;
};
