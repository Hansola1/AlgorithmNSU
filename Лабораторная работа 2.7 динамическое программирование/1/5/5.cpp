#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

struct GanstaData {
    int time, money, width;
};

bool compareGansta(const GanstaData& left, const GanstaData& right)
{
    return left.time < right.time;
}

class moneyGansta {
public:
    std::vector<GanstaData> gansta;
    int countGansta;

    moneyGansta(int countGanstaVal) : countGansta(countGanstaVal) { gansta.resize(countGansta); }

    void fullMoney(std::ostream& os)
    {
        std::vector<int> maxSum(countGansta, 0);

        for (int i = 0; i < countGansta; i++)
        {
            if (gansta[i].width <= gansta[i].time)
            {
                maxSum[i] = gansta[i].money;
                for (int o = 0; o < i; o++) 
                {
                    if (abs(gansta[o].width - gansta[i].width) <= gansta[i].time - gansta[o].time)
                    {
                        maxSum[i] = std::max(maxSum[i], maxSum[o] + gansta[i].money);
                    }
                }
            }
        }

        int sum = 0;
        for (int i = 0; i < countGansta; i++)
        {
            sum = std::max(sum, maxSum[i]);
        }
        os << sum;
    }
};

int main()
{
    int countGansta;
    scanf("%d %*d %*d", &countGansta); // inputFile >> countGansta;
    //*d *d - два следующих целых числа будут проигнорированы.

    std::vector<GanstaData> gansta(countGansta);
    for (int i = 0; i < countGansta; i++)
    {
        scanf("%d", &gansta[i].time);
    }
    for (int i = 0; i < countGansta; i++)
    {
        scanf("%d", &gansta[i].money);
    }
    for (int i = 0; i < countGansta; i++)
    {
        scanf("%d", &gansta[i].width);
    }
    sort(gansta.begin(), gansta.end(), compareGansta);
    //сортирует в порядке возрастания времени

    moneyGansta MoneyGansta(countGansta);
    MoneyGansta.gansta = gansta;

    std::ofstream outputFile("output.txt");
    MoneyGansta.fullMoney(outputFile);

    return 0;
}