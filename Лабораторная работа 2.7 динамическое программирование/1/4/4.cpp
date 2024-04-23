#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

const int len = 1000;
const int mod = 1000000007;

class NumberOfSplits {
public:
    int countPart;
    std::vector<std::vector<int>> part;
    
    NumberOfSplits(int countPartVal) : countPart(countPartVal)
    {
        part.resize(len + 1, std::vector<int>(len + 1));
    }

    int remainsOfPositiveCount()
    {
        int answer = 0;
        for (int i = 0; i < countPart; i++)
        {
            part[i][i] = 1; 
        }

        for (int i = 1; i < countPart; i++) 
        {
            for (int j = 1; j < countPart; j++) 
            {
                for (int s = j; s < countPart; s++)
                {
                    int sum = i + s;
                    if (sum <= countPart) 
                    {
                        part[sum][s] = (part[sum][s] + part[i][j]) % mod;
                    }
                }
            }
        }

        for (int i = 1; i <= countPart; i++) 
        {
            answer = (answer + part[countPart][i]) % mod;
        }
        return answer + 1;
    }

    void remainsPrint(std::ofstream& outputFile)
    {
        int result = remainsOfPositiveCount();
        outputFile << result;
    }
};

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    int countPart;
    inputFile >> countPart;

    NumberOfSplits numberOfSplits(countPart);
    numberOfSplits.remainsPrint(outputFile);

    inputFile.close();
    outputFile.close();

    return 0;
}
