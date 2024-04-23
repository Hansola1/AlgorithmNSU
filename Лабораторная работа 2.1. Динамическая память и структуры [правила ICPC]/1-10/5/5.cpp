#include <iostream>
#include <string>

int calcLetters(char* iStr, int* oLowerCnt, int* oUpperCnt, int* oDigitsCnt)
{
    int LowerCnt = 0, UpperCnt = 0, DigitsCnt = 0, N = 1;
    char c = iStr[N - 1];

    if (iStr[0] == '\0')
    {
        *oLowerCnt = 0;
        *oUpperCnt = 0;
        *oDigitsCnt = 0;

        return 0;
    }

    while (c != '\0')
    {
        if (c < 123 && c > 96)  // a-z
        {
            LowerCnt++;
        }

        if (c < 91 && c > 64) // A - Z
        {
            UpperCnt++;
        }

        if (c < 58 && c > 47) // 0 - 9
        {
            DigitsCnt++;
        }
        N++;
        c = iStr[N - 1];
    }
    *oLowerCnt = LowerCnt;
    *oUpperCnt = UpperCnt;
    *oDigitsCnt = DigitsCnt;

    return N - 1;
}

int main()
{
    int LowerCount = 0, UpperCount = 0, DigitCount = 0;
    int line = 1;

    std::string finishStr;
    while (std::getline(std::cin, finishStr))
    {
        int length = calcLetters(&finishStr[0], &LowerCount, &UpperCount, &DigitCount);
        std::cout << "Line " << line << " has " << length << " chars: " << (LowerCount + UpperCount) << " are letters (" << LowerCount << " lower, " << UpperCount << " upper), " << DigitCount << " are digits." << std::endl;
        line++;
    }
    return 0;
}