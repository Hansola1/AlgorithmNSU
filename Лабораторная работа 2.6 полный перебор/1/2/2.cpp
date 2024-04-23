#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

class ElementInBackpack {
public:
    long long weightElement, priceElement;
};

class ForElemenInBackpack {
public:
    int countElementsInBackpack; long long maxWeightPlayer;
    std::vector<ElementInBackpack> SetElements;

    ForElemenInBackpack(int countElementsInBackpackVal, long long maxWeightPlayerVal, const std::vector<ElementInBackpack>& SetElementsVal) : countElementsInBackpack(countElementsInBackpackVal), maxWeightPlayer(maxWeightPlayerVal), SetElements(SetElementsVal)
    {}

    void find_MinWeightMaxPrice(std::ofstream& outputFile)
    {
        std::vector<int> optimallyElement;
        long long maxPriceElement = 0;

        for (int mask = 0; mask < (1 << countElementsInBackpack); mask++) // 2 в количестве count elem (т.е все возможные варианты)
        {
            long long fullWeight = 0, fullPrice = 0;

            for (int i = 0; i < countElementsInBackpack; i++)
            {
                if (mask & (1 << i)) 
                {
                    fullWeight += SetElements[i].weightElement;
                    fullPrice += SetElements[i].priceElement;
                }
            }

            if (fullWeight <= maxWeightPlayer && fullPrice > maxPriceElement)
            {
                maxPriceElement = fullPrice;
                optimallyElement.clear(); 
                for (int i = 0; i < countElementsInBackpack; i++)
                {
                    if (mask & (1 << i))
                    {
                        optimallyElement.push_back(i + 1); 
                    }
                }
            }
        }

        outputFile << maxPriceElement << " " << optimallyElement.size() << std::endl;
        for (int element : optimallyElement)
        {
            outputFile << element << " ";
        }
    }
};

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    int countElementsInBackpack; long long maxWeightPlayer;
    inputFile >> countElementsInBackpack >> maxWeightPlayer;

    std::vector<ElementInBackpack> SetElements(countElementsInBackpack);
    for (int i = 0; i < countElementsInBackpack; i++)
    {
        inputFile >> SetElements[i].weightElement >> SetElements[i].priceElement;
    }

    ForElemenInBackpack backpack(countElementsInBackpack, maxWeightPlayer, SetElements);
    backpack.find_MinWeightMaxPrice(outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}