#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <time.h>
#include <chrono>

typedef struct DateTime_s
{
    int year, month, day;
    int hours, minutes, seconds;
} DateTime;

DateTime MinDate(const DateTime* arr, int cnt)
{
    DateTime min;
    int y = 6000, m = 123, d = 123, h = 123, mi = 123, s = 123;

    for (int i = 0; i < cnt; i++)
    {
        if (arr[i].year < y)
        {
            min = arr[i];
            y = arr[i].year;
            m = arr[i].month;
            d = arr[i].day;
            h = arr[i].hours;
            mi = arr[i].minutes;
            s = arr[i].seconds;
            continue;
        }

        else if (arr[i].year > y) continue;
        if (arr[i].month < m)
        {
            min = arr[i];
            y = arr[i].year;
            m = arr[i].month;
            d = arr[i].day;
            h = arr[i].hours;
            mi = arr[i].minutes;
            s = arr[i].seconds;
            continue;
        }

        else if (arr[i].month > m) continue;
        if (arr[i].day < d)
        {
            min = arr[i];
            y = arr[i].year;
            m = arr[i].month;
            d = arr[i].day;
            h = arr[i].hours;
            mi = arr[i].minutes;
            s = arr[i].seconds;
            continue;
        }

        else if (arr[i].day > d) continue;
        if (arr[i].hours < h)
        {
            min = arr[i];
            y = arr[i].year;
            m = arr[i].month;
            d = arr[i].day;
            h = arr[i].hours;
            mi = arr[i].minutes;
            s = arr[i].seconds;
            continue;
        }

        else if (arr[i].hours > h) continue;
        if (arr[i].minutes < mi)
        {
            min = arr[i];
            y = arr[i].year;
            m = arr[i].month;
            d = arr[i].day;
            h = arr[i].hours;
            mi = arr[i].minutes;
            s = arr[i].seconds;
            continue;
        }

        else if (arr[i].minutes > mi) continue;
        if (arr[i].seconds < s)
        {
            min = arr[i];
            y = arr[i].year;
            m = arr[i].month;
            d = arr[i].day;
            h = arr[i].hours;
            mi = arr[i].minutes;
            s = arr[i].seconds;
            continue;
        }
        else if (arr[i].seconds > s) continue;
    }
    return min;
}


int main()
{
    int N; std::cin >> N;
    DateTime* dateTime = new DateTime[N];

    for (int i = 0; i < N; i++)
    {
        std::cin >> dateTime[i].year >> dateTime[i].month >> dateTime[i].day >> dateTime[i].hours >> dateTime[i].minutes >> dateTime[i].seconds;
    }

    DateTime answer = MinDate(dateTime, N);
    std::cout << answer.year << ' ' << answer.month << ' ' << answer.day << ' ' << answer.hours << ' ' << answer.minutes << ' ' << answer.seconds;

    delete[] dateTime;
    return 0;
}
