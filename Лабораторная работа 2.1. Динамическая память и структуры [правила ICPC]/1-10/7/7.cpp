#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>

typedef struct Tokens_s {
    int num; // кол-во слов 
    char** arr;
} Tokens;

void tokensSplit(Tokens* tokens, const char* str, const char* delims)
{
    int num = 0, size = strlen(str);

    if (tokens->arr == NULL) // 2. 
    {
        for (int i = 0; i < size; i++)
        {
            while (i < size && str[i] != delims[0] && str[i] != delims[1] && str[i] != delims[2] && str[i] != delims[3])
            {
                i++;
            }
            if (str[i - 1] != delims[0] && str[i - 1] != delims[1] && str[i - 1] != delims[2] && str[i - 1] != delims[3] && i > 0)
            {
                num++;
            }
        }
        tokens->num = num;
        tokens->arr = (char**)malloc(sizeof(char*) * num);
    }

    if (tokens->arr != NULL) //3.
    {
        int fmount = 0;
        for (int i = 0; i < size; i++)
        {
            char* temp = (char*)malloc(sizeof(char));
            int count = 0;
            while (i < size && str[i] != delims[0] && str[i] != delims[1] && str[i] != delims[2] && str[i] != delims[3])
            {
                temp = (char*)realloc(temp, sizeof(char) * (count + 2)); //!!!
                temp[count] = str[i];
                count++; i++;
            }
            if (str[i - 1] != delims[0] && str[i - 1] != delims[1] && str[i - 1] != delims[2] && str[i - 1] != delims[3] && i > 0)
            {
                temp[count] = '\0';
                tokens->arr[fmount] = temp;
                fmount++;
            }
        }
    }
}

void tokensDelete(Tokens* tokens)
{
    for (int i = 0; i < tokens->num; i++)
    {
        free(tokens->arr[i]);
    }

    free(tokens->arr);
    tokens->num = 0;
}

int main()
{
    Tokens t; t.arr = nullptr;
    char delims[] = ".,;:";

    char* str = (char*)malloc(1000001 * sizeof(char));
    std::cin >> str;
    tokensSplit(&t, str, delims);

    std::cout << t.num << std::endl;
    for (int i = 0; i < t.num; i++)
    {
        std::cout << t.arr[i] << std::endl;
    }

    tokensDelete(&t);
    free(str);
    return 0;
}