#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

class ElementInBackpack {
public:
    int weightElement, priceElement;
};

class ForElemenInBackpack {
public:
    int countElements, maxWeight;
    std::vector<ElementInBackpack> setElements;

    ForElemenInBackpack(int countElementsVal, int maxWeightVal) : countElements(countElementsVal), maxWeight(maxWeightVal)
    {
        setElements.resize(countElements + 1);
    }

    void find_MinWeightMaxPrice(std::ofstream& outputFile)
    {
        std::vector<std::vector<int>> optimallyElement(countElements + 1, std::vector<int>(maxWeight + 1, 0));
        int sumWeight = 0, sumPrice = 0;

        for (int i = 1; i <= countElements; i++)
        {
            for (int j = 1; j <= maxWeight; j++)
            {
                if (setElements[i - 1].weightElement > j)
                {
                    optimallyElement[i][j] = optimallyElement[i - 1][j]; 
                }
                else
                {
                    optimallyElement[i][j] = std::max(optimallyElement[i - 1][j], optimallyElement[i - 1][j - setElements[i - 1].weightElement] + setElements[i - 1].priceElement);
                }
            }
        }

        int count = 0, i = countElements, j = maxWeight;
        std::vector<int> chosenItems;

        while (i > 0 && j > 0)
        {
            if (optimallyElement[i][j] != optimallyElement[i - 1][j])
            {
                chosenItems.push_back(i);
                sumWeight += setElements[i - 1].weightElement; 
                sumPrice += setElements[i - 1].priceElement; 

                j -= setElements[i - 1].weightElement; 
                count++;
            }
            i--; 
        }

        outputFile << count << " " << sumWeight << " " << sumPrice << std::endl;
        for (int i = count - 1; i >= 0; i--)
        {
            outputFile << chosenItems[i] << " ";
        }
        outputFile << std::endl;
    }
};

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    int countElements, maxWeight;
    inputFile >> countElements >> maxWeight;

    std::vector<ElementInBackpack> setElements(countElements);
    for (int i = 0; i < countElements; i++)
    {
        inputFile >> setElements[i].weightElement >> setElements[i].priceElement;
    }
    ForElemenInBackpack backpack(countElements, maxWeight);
    backpack.setElements = setElements;
    backpack.find_MinWeightMaxPrice(outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}