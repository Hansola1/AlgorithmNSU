#include <iostream>
#include <fstream>

class Node_C {
public:
    int data;
    Node_C* next;

    Node_C(int data)
    {
        this->data = data;
        this->next = nullptr;
    }
};

class ListFullQueue_C {
public:
    Node_C* head = nullptr;
    Node_C* tail = nullptr;
    int size = 0;

    void pushTail(int data)
    {
        Node_C* node = new Node_C(data);

        if (head == nullptr)
        {
            head = node;
        }
        if (tail != nullptr)
        {
            tail->next = node;
        }
        tail = node;
        size++;
    }

    void pop()
    {
        Node_C* tmp = head;
        head = head->next;
        delete tmp;
        size--;

        if (head == nullptr)
        {
            tail = nullptr;
        }
    }

    void deleteList()
    {
        Node_C* tmp;
        while (head != nullptr)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }
        size = 0;
    }
};

void BuffOfCommand(std::ifstream& inputFile, std::ofstream& outputFile, int lenBuff, int numElem)
{
    ListFullQueue_C* queue = new ListFullQueue_C;

    int command, data;
    while (inputFile >> command)
    {
        if (command >= 0)
        {
            int freePlace = lenBuff - queue->size;
            // из общ длины буфера вычитаем текущ
            for (int j = 0; j < command; j++)
            {
                inputFile >> data;
                if (queue->size < lenBuff)
                {
                    queue->pushTail(data);
                }
                else if (freePlace == j)
                {
                    outputFile << "Memory overflow" << std::endl;
                }
            }
        }

        if (command < 0)
        {
            int count = -command;
            if (queue->size < count)
            {
                int sum = 0;
                Node_C* tmp = queue->head;
                while (tmp != nullptr)
                {
                    sum += tmp->data;
                    tmp = tmp->next;
                }
                if (queue->size != 0)
                {
                    outputFile << sum / queue->size << std::endl;
                }
                queue->deleteList();
                outputFile << "Empty queue" << std::endl;

            }
            else
            {
                int sum = 0;
                for (int j = 0; j < count; ++j)
                {
                    sum += queue->head->data;
                    queue->pop();
                }
                outputFile << sum / count << std::endl;
            }
        }
    }
    delete queue;
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    int lenBuff, numElem;
    inputFile >> lenBuff >> numElem;
    BuffOfCommand(inputFile, outputFile, lenBuff, numElem);

    outputFile.close();
    return 0;
}
