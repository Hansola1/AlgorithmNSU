#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

void reverse(char* start, int len)
{
    for (int i = len - 1; i >= 0; i--)
    {
        std::cout << start[i];
    }
    std::cout << std::endl;
}

int main()
{
    int N; std::cin >> N;

    for (int i = 0; i < N; i++)
    {
        std::string str;
        std::cin >> str;

        char* ptr = &str[0];
        reverse(ptr, str.length());
    }

    return 0;
}