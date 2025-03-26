#include "BaseBallLogic.h"

FString UBaseBallLogic::GenerateUniqueRandomNumber()
{
    TArray<int32> Numbers;
    for (int32 i = 1; i <= 9; i++) Numbers.Add(i);

    FString Result;
    for (int32 i = 0; i < 3; i++)
    {
        int32 Index = FMath::RandRange(0, Numbers.Num() - 1);
        Result.Append(FString::FromInt(Numbers[Index]));
        Numbers.RemoveAt(Index);
    }
    return Result;
}

bool UBaseBallLogic::IsValidInput(const FString& Input)
{
    FString ModifiedInput = Input;  // Input을 복사하여 수정 가능하도록 함

    ModifiedInput = ModifiedInput.RightChop(1);  // 첫 번째 문자("/")를 제거한 새로운 문자열로 변경

    if (ModifiedInput.Len() != 3) return false;  // 2. 3자리인지 확인

    TSet<TCHAR> UniqueChars;
    for (TCHAR Char : ModifiedInput)
    {
        if (!FChar::IsDigit(Char) || Char == '0') return false;  // 3. 숫자 검사
        UniqueChars.Add(Char);
    }

    return UniqueChars.Num() == 3;
}


void UBaseBallLogic::CalculateScore(const FString& TargetNumber, const FString& Guess, int32& Strikes, int32& Balls)
{
    Strikes = 0;
    Balls = 0;

    for (int32 i = 0; i < TargetNumber.Len(); ++i)
    {
        for (int32 j = 0; j < Guess.Len(); ++j)
        {
            if (TargetNumber[i] == Guess[j])  // 숫자가 동일한 경우
            {
                if (i == j)  // 자리가 일치하면 스트라이크
                {
                    Strikes++;
                }
                else  // 자리는 다르지만 숫자가 같으면 볼
                {
                    Balls++;
                }
            }
        }
    }
}


