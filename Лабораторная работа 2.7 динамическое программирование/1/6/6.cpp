#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

class SequenceCalculator {
public:
    std::vector<long long> sequence;
    int len;

    SequenceCalculator(int LenSequenceVal) : len(LenSequenceVal) { sequence.resize(len); }

    void BuildMaxSequence(std::ofstream& outputFile)
    {
        int maxLen = 1; 
        int idxEnd = 0;

        std::vector<long long> maxSequence(len, 1); 
        std::vector<long long> parents(len, -1); 

        for (int i = 1; i < len; i++) 
        {
            for (int j = 0; j < i; j++) 
            {
                if (sequence[i] > sequence[j] && maxSequence[i] < maxSequence[j] + 1)
                {
                    maxSequence[i] = maxSequence[j] + 1; 
                    if (maxSequence[i] > maxLen) 
                    {
                        maxLen = maxSequence[i]; 
                        idxEnd = i; 
                    }
                    parents[i] = j;
                }
            }
        }
        outputFile << maxLen << std::endl;

        std::vector<long long> answer(maxLen);
        std::vector<long long> idxs(maxLen);
        idxs[maxLen - 1] = idxEnd + 1;
        answer[maxLen - 1] = sequence[idxEnd];

        for (int i = idxEnd - 1; i >= 0; i--) 
        {
            if (sequence[i] < sequence[idxEnd] && maxSequence[i] == maxSequence[idxEnd] - 1)
            {
                maxLen--;

                idxs[maxLen - 1] = i + 1;
                answer[maxLen - 1] = sequence[i];
                idxEnd = i;
            }
        }

        for (int i = 0; i < answer.size(); i++)
        {
            outputFile << 'A' << '[' << idxs[i] << ']' << " = " << answer[i] << std::endl;
        }
    }
};

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    int len;
    inputFile >> len;

    std::vector<long long> num(len);
    for (int i = 0; i < len; i++)
    {
        inputFile >> num[i];
    }

    SequenceCalculator sequenceCalculator(len);
    sequenceCalculator.sequence = num;
    sequenceCalculator.BuildMaxSequence(outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}