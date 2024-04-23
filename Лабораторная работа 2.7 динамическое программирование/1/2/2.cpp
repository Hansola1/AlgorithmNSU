#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

class SequenceСalculator {
public:
    int lenSequence, divide;
    std::vector<int> sequence;

    SequenceСalculator(int lenSequenceVal, int divideVal) : lenSequence(lenSequenceVal), divide(divideVal) 
    { sequence.resize(lenSequence); }

    void whoIsDivide(std::ofstream& outputFile)
    {
        std::vector<bool> sequenceF(divide, false);
        sequenceF[0] = true; 

        for (int numSequence : sequence)
        {
            std::vector<bool> next(sequenceF.size(), false);

            for (int i = 0; i < sequenceF.size(); i++)
            {
                if (sequenceF[i]) 
                {
                    next[(i + numSequence % divide + divide) % divide] = true; 
                    next[(i - numSequence % divide + divide) % divide] = true; 
                }
            }
            sequenceF = next;
        }

        if (sequenceF[0]) 
        {
            outputFile << "Divisible" << std::endl;
        }
        else
        {
            outputFile << "Not divisible" << std::endl;
        }             
    }
};

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    int lenSequence, divide;
    inputFile >> lenSequence >> divide;

    std::vector<int> sequence(lenSequence);
    for (int i = 0; i <lenSequence; i++)
    {
        inputFile >> sequence[i];
    }

    SequenceСalculator sequenceСalculator(lenSequence, divide);
    sequenceСalculator.sequence = sequence;
    sequenceСalculator.whoIsDivide(outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}