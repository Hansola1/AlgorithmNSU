#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

class arrayTableCell 
{
public:
    int len = 0; std::vector<int> arr;
    arrayTableCell() : arr(len) { }
};

class HashTableF {
public:
    const int TableSize = 2000; //1000!!!
    std::vector<arrayTableCell> table;
    std::vector<int> finalTablePrint;
    int count = 0;

    HashTableF() : table(TableSize) { }
    int hash(int i)
    {
        return (i % 1000) + 999;
    }

    void pushInKey(int i, std::ifstream& inputFile, std::ofstream& outputFile)
    {
        int key = hash(i);
        if (table[key].len == 0)
        {
            finalTablePrint.push_back(i);
            count++;
            table[key].arr.push_back(i);
            table[key].len++;
        }
        else
        {
            if (dublicBublic(key, i))
            {
                finalTablePrint.push_back(i);
                count++;
                table[key].arr.push_back(i);
                table[key].len++;
            }
        }
    }
    bool dublicBublic(int key, int i)
    {
        return std::find(table[key].arr.begin(), table[key].arr.end(), i) == table[key].arr.end();
    }
};

int main()
{
    std::ifstream inputFile("input.bin", std::ios::binary);
    std::ofstream outputFile("output.bin", std::ios::out | std::ios::binary);
    long len; HashTableF hashTableF;
    inputFile.read(reinterpret_cast<char*>(&len), sizeof(long));

    long* arr = new long[len];
    for (int i = 0; i < len; i++)
    {
        inputFile.read(reinterpret_cast<char*>(&arr[i]), sizeof(long));
        hashTableF.pushInKey(arr[i], inputFile, outputFile);
    }
    outputFile.write(reinterpret_cast<char*>(&hashTableF.count), sizeof(long));

    for (int i = 0; i < hashTableF.finalTablePrint.size(); i++)
    {
        outputFile.write(reinterpret_cast<char*>(&hashTableF.finalTablePrint[i]), sizeof(long));
    }

    outputFile.close();
    delete[] arr;
    return 0;
}