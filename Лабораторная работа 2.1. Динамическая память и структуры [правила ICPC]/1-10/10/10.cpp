#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <iomanip>  // для %0.15g

void XorToDouble(int N, int &P, int &Q, long long &M)
{
    union // одна обл в памяти хранит неск переменных, 4 бит
    {
        long long M;
        double answer;
    } u1;

    for (int i = 0; i < N; i++)
    {
        u1.answer = static_cast<double>(P) / Q; // = X
        u1.M = M ^ (u1.M);
        //  с преобразованным значением u1.M. Это означает, что каждый бит в M будет инвертирован, если соответствующий бит в u1.M равен 1.
    }

    std::cout << std::setprecision(15) << u1.answer << std::endl;
}

int main()
{
    int N; std::cin >> N;
    int P; int Q; //числитель, знаменатель 
    long long M;
   
    for (int i = 0; i < N; i++)
    {
        scanf("%d/%d xor %llx", &P, &Q, &M);
        // %longlong
        XorToDouble(N, P, Q, M);
    }

    return 0;
}