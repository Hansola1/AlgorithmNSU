#include <iostream>
#include <vector>
#include <deque>
#include <fstream>

class Heap
{
public:
    std::vector<int> heap;

    void command(std::vector<int>& A, int N, std::ifstream& inputFile, std::ofstream& outputFile)
    {
        std::deque<int> window;
        char operand;
        int L = 0, R = 0;

        for (int i = 0; i < N; i++)
        {
            inputFile >> A[i];
        }
           
        while (inputFile >> operand)
        {
            if (operand == 'R')
            {
                if (R < N)
                {
                    while (!window.empty() && A[window.back()] <= A[R])
                    {
                        window.pop_back();
                    }
                    window.push_back(R);
                    R++;
                }
            }
            else if (operand == 'L')
            {
                if (L < R) {
                    if (!window.empty() && window.front() == L)
                    {
                        window.pop_front();
                    }
                    L++;
                }
            }

            if (!window.empty())
            {
                outputFile << A[window.front()] << "\n";
            }
            else
            {
                outputFile << "0\n";
            }
        }
    }
};

int main() 
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    Heap heap;
    int N; inputFile >> N;

    std::vector<int> arr(N);
    heap.command(arr, N, inputFile, outputFile);

    outputFile.close();
    return 0;
}