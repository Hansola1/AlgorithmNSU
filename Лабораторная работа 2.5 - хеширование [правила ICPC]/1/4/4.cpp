#include <iostream> 
#include <sstream>
#include <fstream> 
#include <vector> 
#include <cmath> 
#include <unordered_map>

//0 1 2 3 0 4 5 6 0 1 2 3 0

/*class stringAndIntInCell
{
public:
    int countForKey = 0;
    std::string splitStr = "";
};

class arrayTableCell
{
public:
    std::vector<stringAndIntInCell> arr;
};

class HashTableF
{
public:
    int lenStr, lenStrPattern;
    int TableSize = 0;
    std::vector<arrayTableCell> ElemsInHashTable;
    std::string strIn;

    HashTableF(int lenStrVal, int lenStrPatternVal, std::string strVal) : lenStr(lenStrVal), lenStrPattern(lenStrPatternVal), strIn(strVal) {
        TableSize = lenStr - lenStrPattern + 1;
        ElemsInHashTable.resize(TableSize);
    }
    int hash(std::string& splitStr)
    {
        int hash = 0;
        for (char c : splitStr) //(size_t i = 0; i < lenStrPattern; i++)
        {
            hash = (hash * 31) + c; //(hash * 10) + tmpSplitStr[i] - '0';
        }
        hash = std::abs(hash % 12);
        return hash % TableSize;
    }

    bool IsThere(std::string& splitStr, int key)
    {
        if (ElemsInHashTable[key].arr.size() != 0)
        {
            for (int i = 0; i < ElemsInHashTable[key].arr.size(); i++)
            {
                if (ElemsInHashTable[key].arr[i].splitStr == splitStr)
                {
                    return 1;
                }
            }
        }
        return 0;
    }

    void colorsForSplitStr(std::ofstream& outputFile)
    {
        std::string splitStr;
        int count = 0;

        for (int i = 0; i < TableSize; i++)
        {
            splitStr = strIn.substr(i, lenStrPattern);
            int key = hash(splitStr);

            if (IsThere(splitStr, key) == 0)
            {
                stringAndIntInCell tmp;
                tmp.splitStr = splitStr;
                tmp.countForKey = count;

                ElemsInHashTable[key].arr.push_back(tmp);
                outputFile << count << " ";
                count++;
            }
            else
            {
                for (int j = 0; j < ElemsInHashTable[key].arr.size(); j++)
                {
                    if (ElemsInHashTable[key].arr[j].splitStr == splitStr)
                    {
                        outputFile << ElemsInHashTable[key].arr[j].countForKey << " ";
                        break;
                    }
                }
            }
        }
    }
}; */

const int maxLenStr = 1000000;
const int maxLenStrPattern = 1000000;

int lenStrIn, lenStrPattern, countPattern;
char strIn[maxLenStr];

unsigned long long hashValuesStrIn[maxLenStr], powerValues[maxLenStrPattern];
std::unordered_map<unsigned long long, int> colorAndNum;

class HashTableF {
public:

    void calculatePowerForHash() 
    {
        powerValues[0] = 1;  
        for (int i = 1; i <= lenStrPattern; i++)
        {
            powerValues[i] = powerValues[i - 1] * 31;
        }
    }

    void calculateHash()

    {
        for (int i = 1; i <= lenStrIn; i++)
        {
            hashValuesStrIn[i] = hashValuesStrIn[i - 1] * 31 + strIn[i];
            if (i >= lenStrPattern)
            {
                unsigned long long currentHashInPattern = hashValuesStrIn[i] - hashValuesStrIn[i - lenStrPattern] * powerValues[lenStrPattern];
                if (colorAndNum.count(currentHashInPattern) == 0)
                {
                    colorAndNum[currentHashInPattern] = colorAndNum.size();
                }
            }
        }
    }

    void printColorAndNum(std::ofstream& outputFile)
    {
        for (int i = 1; i <= countPattern; i++)
        {
            unsigned long long currentHashInPattern = hashValuesStrIn[i + lenStrPattern - 1] - hashValuesStrIn[i - 1] * powerValues[lenStrPattern];
            outputFile << colorAndNum[currentHashInPattern] << " ";
        }
        outputFile << std::endl;
    }
};


int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    inputFile >> lenStrIn >> lenStrPattern >> strIn + 1;
    countPattern = lenStrIn - lenStrPattern + 1;

    HashTableF hashTableF;  
    hashTableF.calculatePowerForHash();
    hashTableF.calculateHash();
    hashTableF.printColorAndNum(outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}