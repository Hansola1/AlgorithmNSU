#include <iostream>
#include <fstream>
#include <string>
#include <list>

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

class ListFull_C {
public:
    Node_C* head = nullptr;
    Node_C* tail = nullptr;

    void pushHead(int data)
    {
        Node_C* node = new Node_C(data);
        node->next = head;
        head = node;

        if (node->next == nullptr)
        {
            tail = head;
        }
    }

    void merge(ListFull_C& listTwo)
    {
        Node_C* tmp = head;

        while (listTwo.head != nullptr) // 1
        {
            if (listTwo.head->data > tmp->data && tmp == head)
            {
                Node_C* tmpStart = listTwo.head->next; 

                listTwo.head->next = tmp; 
                head = listTwo.head;  
               
                tmp = head; 
                listTwo.head = tmpStart;
            }

            else
            {
                while (tmp != nullptr && tmp->next != nullptr && listTwo.head->data < tmp->next->data)
                {
                    tmp = tmp->next;
                }
                Node_C* tmpLose = listTwo.head; 
                listTwo.head = listTwo.head->next; 

                tmpLose->next = tmp->next;
                tmp->next = tmpLose;
            }
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
    }
};


int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    int lenListOne, lenListTwo, data;
    inputFile >> lenListOne >> lenListTwo;
    ListFull_C listOne, listTwo;

    for (int i = 0; i < lenListOne; i++)
    {
        inputFile >> data;
        listOne.pushHead(data);
    }
    for (int i = 0; i < lenListTwo; i++)
    {
        inputFile >> data;
        listTwo.pushHead(data);
    }


    listOne.merge(listTwo);
    Node_C* start = listOne.head;
    while (start != nullptr)
    {
        outputFile << start->data << ' ';
        start = start->next;
    }

    listOne.deleteList();
    listTwo.deleteList();
    outputFile.close();
    return 0;
}
