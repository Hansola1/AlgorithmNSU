#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstring>
#include <stdio.h>

char* concat(char* pref, char* suff)   //= strcat(pref, suff);
{
    int i = strlen(pref);
    int j = 0;

    while (suff[j] != '\0')
    {
        pref[i] = suff[j];
        i++; j++;
    }
    pref[i] = '\0';

    return pref + i; 
}

int main()
{
    int N; std::cin >> N;

    char* str = (char*)malloc(sizeof(char) * 1000001);
    char* tmp = (char*)malloc(sizeof(char) * 101);

    for (int i = 0; i <= N; i++)   //(str[i] != '\n')
    {
        gets(tmp);
        concat(str, tmp);
    }
    std::cout << str << std::endl;

    free(str);
    free(tmp);
    return 0;
}