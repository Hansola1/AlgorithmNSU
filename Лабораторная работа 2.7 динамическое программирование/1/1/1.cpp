#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

class SequenceСalculator {
public:
    int lenSequence;
    SequenceСalculator(int LenSequenceVal) : lenSequence(LenSequenceVal) {}

    void whoIsSequenceLen(std::ofstream& outputFile)
    {
        std::vector<std::vector<int>> sequenceForNull(lenSequence + 1, std::vector<int>(2, 0));

        sequenceForNull[1][0] = sequenceForNull[1][1] = 1; 

        for (int i = 2; i <= lenSequence; i++)
        {
            sequenceForNull[i][0] = sequenceForNull[i - 1][0] + sequenceForNull[i - 1][1];
            sequenceForNull[i][1] = sequenceForNull[i - 1][0]; 
        }
        int FullSequences = sequenceForNull[lenSequence][0] + sequenceForNull[lenSequence][1];

        outputFile << FullSequences << std::endl;
    }
};

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    int LenSequence; inputFile >> LenSequence;

    SequenceСalculator sequenceСalculator(LenSequence);
    sequenceСalculator.whoIsSequenceLen(outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}