#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>

class PhoneCalculator {
public:
    std::unordered_map<char, std::string> NameAndNum;
    std::string name, number;

    PhoneCalculator(std::string nameVal, std::string numberVal) : name(nameVal), number(numberVal) { }

    void convert(std::ofstream& outputFile)
    {
        int count = 0;
        for (char digit : number)
        {
            std::string letters = NameAndNum[digit];
            int currentIdx = 0;

            for (char letter : letters)
            {
                if (currentIdx < name.size() && letter == std::toupper(name[currentIdx])) 
                {
                    count++;
                    currentIdx++;
                }
            }
        }
        outputFile << count; //<< std::endl;
    }
};

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    std::string name; inputFile >> name;
    std::string number; inputFile >> number;

    PhoneCalculator phoneCalculator(name, number);
    phoneCalculator.NameAndNum = {
        {'1', ""},
        {'2', "ABC"},
        {'3', "DEF"},
        {'4', "GHI"},
        {'5', "JKL"},
        {'6', "MN"},
        {'7', "PRS"},
        {'8', "TUV"},
        {'9', "WXY"},
        {'0', "OQZ"},
    };
    phoneCalculator.convert(outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}