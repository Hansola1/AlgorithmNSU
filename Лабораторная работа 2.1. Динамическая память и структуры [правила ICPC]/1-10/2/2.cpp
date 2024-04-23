#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

/*typedef struct Time_s
{
	int hours, minutes, seconds;
} Time; */

int readTime(char* iStr, int* oHours, int* oMinutes, int* oSeconds)
{
	int hours, minutes, seconds;
	int finishDate = sscanf(iStr, "%d: %d: %d", &hours, &minutes, &seconds);

	if (finishDate == 2)
	{
		seconds = 0;
		finishDate = 3;
	}

	if (finishDate == 3)
	{
		if (hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59 && seconds >= 0 && seconds <= 59)
		{
			if (oHours != NULL)
			{
				*oHours = hours;
			}
			if (oMinutes != NULL)
			{
				*oMinutes = minutes;
			}
			if (oSeconds != NULL)
			{
				*oSeconds = seconds;
			}
			return 1;
		}

		else
		{
			if (oHours != NULL)
			{
				*oHours = -1;
			}
			if (oMinutes != NULL)
			{
				*oMinutes = -1;
			}
			if (oSeconds != NULL)
			{
				*oSeconds = -1;
			}

			return 0;
		}
	}


	char exception = '|';
	for (int i = 0; i < strlen(iStr); i++)
	{
		if (iStr[i] == exception)
		{
			if (oHours != NULL)
			{
				*oHours = -1;
			}
			if (oMinutes != NULL)
			{
				*oMinutes = -1;
			}
			if (oSeconds != NULL)
			{
				*oSeconds = -1;
			}
		}
	}
	return 0;
}

int main()
{
	int oHours, oMinutes, oSeconds;
	char iStr[16]; std::cin >> iStr;

	readTime(iStr, &oHours, &oMinutes, &oSeconds);
	std::cout << readTime(iStr, &oHours, &oMinutes, &oSeconds) << " " << oHours << " " << oMinutes << " " << oSeconds << std::endl;

	readTime(iStr, &oHours, &oMinutes, NULL);
	std::cout << readTime(iStr, &oHours, &oMinutes, NULL) << " " << oHours << " " << oMinutes << std::endl;

	readTime(iStr, &oHours, NULL, NULL);
	std::cout << readTime(iStr, &oHours, NULL, NULL) << " " << oHours << std::endl;

	return 0;
}