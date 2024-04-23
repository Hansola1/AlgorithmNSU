#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

class HashTableF {
public:
    uint64_t a, b, c, M;

    HashTableF(uint64_t a_val, uint64_t b_val, uint64_t c_val, uint64_t M_val) : a(a_val), b(b_val), c(c_val), M(M_val) {}

    uint64_t func(uint64_t s)
    {
        return (s * s * a + s * b + c) % M;
    }

    void findRepeatedSegment(std::ofstream& outputFile)
    {
        uint64_t state = 1;
        std::unordered_map<uint64_t, uint64_t> stateMap;
        stateMap[state] = 0; 

        uint64_t l = -1, r = M + 1;
        uint64_t pos = 1;

        while (true)
        {
            state = func(state); 

            if (stateMap.find(state) != stateMap.end())
            {
                l = stateMap[state]; 
                r = pos;
                break;
            }
            stateMap[state] = pos;
            pos++;
        }
        outputFile << l << " " << r;
    }
};

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    uint64_t M, a, b, c;
    inputFile >> M >> a >> b >> c;

    HashTableF hashTableF(a, b, c, M);
    hashTableF.findRepeatedSegment(outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}