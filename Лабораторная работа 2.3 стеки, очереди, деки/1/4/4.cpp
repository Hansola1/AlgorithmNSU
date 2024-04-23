#include <iostream>
#include <fstream>

class deque
{
private:
    int lim, head, tail;
    int* data;

public:
    deque(int max)
    {
        head = -1;
        tail = 0;
        lim = max;
        data = new int[max];
    }
    ~deque()
    {
        delete[] data;
    }

    bool empty() const
    {
        return (head == -1);
    }

    void pushHead(const int value)
    {
        if (head == -1) head = tail = 0;
        else if (head == 0) head = lim - 1;
        else head--;

        data[head] = value;
    }
    void pushTail(const int value)
    {
        if (head == -1) head = tail = 0;
        else if (tail == lim - 1) { tail = 0; }
        else tail++;
        data[tail] = value;
    }

    int popHead()
    {
        if (empty()) return 0;
        int value = data[head];

        if (head == tail) head = tail = -1;
        else if (head == lim - 1) head = 0;
        else head++;
        return value;
    }
    int popTail()
    {
        if (empty()) return 0;
        int value = data[tail];

        if (head == tail) head = tail = -1;
        else if (tail == 0)  tail = lim - 1;
        else tail--;

        return value;
    }

    int size() const
    {
        if (empty()) return 0;

        if (head <= tail) return tail - head + 1;

        return lim - head + tail + 1;
    }
    void print()
    {
        int s = size();
        std::cout << s << "  ";
        for (int i = 0; i < s; i++)
        {
            std::cout << popHead() << ' ';
        }
        std::cout << std::endl;
    }
};

int hexToDec(char c) // 16 в 10
{
    if (c >= 'A')
    {
        return c - 'A' + 10;
    }
    return c - '0';
}//Например, если c = 'B', то функция вернет 11 (10 + ('B' - 'A')

void processOperations(std::ifstream& inputFile, int N_Card, int M_Operation)
{
    deque rightDeck(N_Card * 2 + 1);
    deque leftDeck(N_Card * 2 + 1);

    for (int i = 1; i <= N_Card; i++) 
    {
        rightDeck.pushTail(-i);
        leftDeck.pushTail(i);
    }

    for (int i = 0; i < M_Operation; i++)
    {
        char operation;
        inputFile >> operation;
        int commands = hexToDec(operation);

        int fromWhich = (commands >> 3) & 1;
        int fromWhere = (commands >> 2) & 1;
        int inWhich = (commands >> 1) & 1;
        int inWhere = commands & 1; 

        int card;
        if (fromWhich == 1)
        {
            if (fromWhere == 1)
            {
                card = rightDeck.popTail();
            }
            else
            {
                card = rightDeck.popHead();
            }
        }
        else
        {
            if (fromWhere == 1)
            {
                card = leftDeck.popTail();
            }
            else
            {
                card = leftDeck.popHead();
            }
        }

        if (card)
        {
            if (inWhich == 1)
            {
                if (inWhere == 1)
                {
                    rightDeck.pushTail(card);
                }
                else
                {
                    rightDeck.pushHead(card);
                }
            }
            else
            {
                if (inWhere == 1)
                {
                    leftDeck.pushTail(card);
                }
                else
                {
                    leftDeck.pushHead(card);
                }
            }
        }
    }
    leftDeck.print();
    rightDeck.print();
}

int main()
{
    int N_Card, M_Operation;
    std::ifstream inputFile("input.txt");
    inputFile >> N_Card >> M_Operation;

    processOperations(inputFile, N_Card, M_Operation);
    return 0;
}