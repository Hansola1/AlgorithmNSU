#include <iostream>
#include <vector>
#include <unordered_map>

class HashTableF {
public:
    uint32_t key;

    uint32_t hashFunction(uint32_t key)
    {
        return key % 1000;
    }

    void commandPrint(std::ostream& os)
    {
        std::unordered_map<uint32_t, uint32_t> hashTab;
        uint32_t key = 1;  

        while (true)
        {
            os << "eval " << key << std::endl;

            uint32_t hashForX;
            std::cin >> hashForX;
            if (hashTab.find(hashForX) != hashTab.end()) 
            {
                os << "answer " << key << " " << hashTab[hashForX] << std::endl;
                //os.flush();
                break;
            }
            hashTab[hashForX] = key;
            key++;
        }
    }
};

int main()
{
    HashTableF hashTableF;
    hashTableF.commandPrint(std::cout);

    return 0;
}