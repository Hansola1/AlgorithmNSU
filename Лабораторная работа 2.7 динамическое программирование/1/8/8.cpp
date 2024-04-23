#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

class SequenceCalculator {
public:
    std::vector<int> sequence;
    int len;

    SequenceCalculator(int LenSequenceVal) : len(LenSequenceVal) { sequence.resize(len); }

    void BuildMaxSequence(std::ofstream& outputFile)
    {
        std::vector<int> subseq; 
        std::vector<int> parents(len, -1); 
        std::vector<int> idxs(len);

        for (int i = 0; i < len; i++) 
        {
            auto it = std::lower_bound(subseq.begin(), subseq.end(), sequence[i]); // it - место в векторе subseq

            if (it == subseq.end()) 
            {
                parents[i] = subseq.empty() ? -1 : idxs[subseq.size() - 1];

                idxs[subseq.size()] = i; 
                subseq.push_back(sequence[i]); 
            }

            else
            {
                *it = sequence[i];
                parents[i] = it == subseq.begin() ? -1 : idxs[(it - subseq.begin()) - 1];

                idxs[it - subseq.begin()] = i;
            }
        }

        std::vector<int> answer;
        int i = idxs[subseq.size() - 1]; 
        while (i >= 0) 
        {
            answer.push_back(i);
            i = parents[i];
        }
        std::reverse(answer.begin(), answer.end()); 

        outputFile << answer.size() << std::endl;
        for (int i : answer) //(int i = 0; i < answer.size(); i++)
        {
            outputFile << 'A' << '[' << i + 1 << ']' << " = " << sequence[i] << std::endl;
        }
    }
};

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    int len; inputFile >> len;

    std::vector<int> num(len);
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