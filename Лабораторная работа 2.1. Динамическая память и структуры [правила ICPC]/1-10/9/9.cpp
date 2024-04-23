#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

typedef struct String_S
{
    char* str;
    int idx_S;
    struct String_S* next; 
} string;

void stringDelete(string* arr)
{
    string* tmp = arr; 
    while (tmp->next != NULL) 
    {
        tmp = tmp->next; 
        delete[] arr;
        arr = tmp; 
    }  
}

void stringAdd(string** arr, int* idx_S, int ind)
{
    char* str = (char*)malloc(sizeof(char) * (ind + 1)); // +1 = \C
    std::cin >> str;

    *arr = (string*)realloc(*arr, sizeof(string) * (*idx_S + 1));
    (*arr)[*idx_S].idx_S = *idx_S;
    (*arr)[*idx_S].next = nullptr; 
    (*arr)[*idx_S].str = str;
    (*idx_S)++; 
}

void stringPrint(string* arr, int ind)
{
    std::cout << arr[ind].str << std::endl;
}

void countCharInString(string* arr, int ind)
{
    char s; std::cin >> s;
    int count = 0;

    for (int i = 0; i < strlen(arr[ind].str); i++)
    {
        if (arr[ind].str[i] == s)
        {
            count++;
        }
    }
    std::cout << count << std::endl;
}

int main()
{
    int N; std::cin >> N;
    int typeOfRequest;
    int ind; int idx_S = 0;

    string* arr = nullptr; 
    for (int j = 0; j < N; j++)
    {
        std::cin >> typeOfRequest >> ind;

        if (typeOfRequest == 0)
        {
            stringAdd(&arr, &idx_S, ind);
        }

        if (typeOfRequest == 1)
        {
            arr[ind].idx_S = -1;
        }

        if (typeOfRequest == 2)
        {
            stringPrint(arr, ind);
        }

        if (typeOfRequest == 3)
        {
            countCharInString(arr, ind);
        }
    }

    stringDelete(arr); //delete[] arr; !!!
    return 0;
}

