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
    FString ModifiedInput = Input;  // Input�� �����Ͽ� ���� �����ϵ��� ��

    ModifiedInput = ModifiedInput.RightChop(1);  // ù ��° ����("/")�� ������ ���ο� ���ڿ��� ����

    if (ModifiedInput.Len() != 3) return false;  // 2. 3�ڸ����� Ȯ��

    TSet<TCHAR> UniqueChars;
    for (TCHAR Char : ModifiedInput)
    {
        if (!FChar::IsDigit(Char) || Char == '0') return false;  // 3. ���� �˻�
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
            if (TargetNumber[i] == Guess[j])  // ���ڰ� ������ ���
            {
                if (i == j)  // �ڸ��� ��ġ�ϸ� ��Ʈ����ũ
                {
                    Strikes++;
                }
                else  // �ڸ��� �ٸ����� ���ڰ� ������ ��
                {
                    Balls++;
                }
            }
        }
    }
}


