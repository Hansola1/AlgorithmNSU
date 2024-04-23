#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

typedef struct Label_s {
    char name[16];
    int age;
} Label;


typedef struct NameStats_s {
    int cntTotal;
    int cntLong; // >10 
} NameStats;

typedef struct AgeStats_s {
    int cntTotal;
    int cntAdults;
    int cntKids;  //<14 
} AgeStats;

void calcStats(const Label* arr, int cnt, NameStats* oNames, AgeStats* oAges)
{
    oNames->cntTotal = cnt;
    oNames->cntLong = 0;
    oAges->cntTotal = cnt;
    oAges->cntAdults = 0;
    oAges->cntKids = 0;

    for (int i = 0; i < cnt; i++)
    {
        if (strlen(arr[i].name) > 10)
        {
            oNames->cntLong++;
        }
        if (arr[i].age >= 18)
        {
            oAges->cntAdults++;
        }
        else if (arr[i].age < 14)
        {
            oAges->cntKids++;
        }
    }
}


int main()
{
    int N;  std::cin >> N;
    Label* arr = new Label[N];

    std::string let = "let";
    for (int i = 0; i < N; i++)
    {
        std::cin >> arr[i].name >> arr[i].age >> let;
    }

    NameStats ONames;
    AgeStats OAges;
    calcStats(arr, N, &ONames, &OAges);

    std::cout << "names: total = " << ONames.cntTotal << std::endl << "names: long = " << ONames.cntLong << std::endl;
    std::cout << "ages: total = " << OAges.cntTotal << std::endl << "ages: adult = " << OAges.cntAdults << std::endl << "ages: kid = " << OAges.cntKids << std::endl;

    delete[] arr;
    return 0;
}