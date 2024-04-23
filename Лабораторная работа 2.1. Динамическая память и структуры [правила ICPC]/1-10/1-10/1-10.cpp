#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

void printTime(int hour, int minutes, int seconds)
{
    //std::cout << hour << ":" << minutes << ":" << seconds;
    printf("%02d:", hour); printf("%02d:", minutes); printf("%02d\n", seconds);
}

int main()
{
    int N; std::cin >> N;
    int hour, minutes, seconds;

    for (int i = 0; i < N; i++)
    {
        std::cin >> hour >> minutes >> seconds;
        printTime(hour, minutes, seconds);
    }

    return 0;
}
