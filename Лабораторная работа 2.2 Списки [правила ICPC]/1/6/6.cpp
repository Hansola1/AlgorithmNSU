#include <iostream>
#include <fstream>
#include <string>
#include <list>

class Node_C {
public:
    int data;
    Node_C* next;
    Node_C* previous;

    Node_C(int data)
    {
        this->data = data;
        this->next = nullptr;
        this->previous = nullptr;
    }
};

class ListFull_C {
public:
    Node_C* head = nullptr;

    void pushTailCycle(int data)
    {
        Node_C* node = new Node_C(data);

        if (head == nullptr)
        {
            head = node;
            head->next = head; 
            head->previous = head;
        }

        else 
        {
            node->previous = head->previous; 
            node->next = head;

            head->previous->next = node;
            head->previous = node;
        }
    }

    int Del_K(int DelInd_K)
    {
        Node_C* tmp = head;

        while (tmp->next != tmp) 
        {
            for (int k = 0; k < (DelInd_K - 1); k++)  
            {
                tmp = tmp->next;
            }
            Node_C* toDelete = tmp;
            tmp = toDelete->next; 

            toDelete->previous->next = toDelete->next; 
            toDelete->next->previous = toDelete->previous;

            if (toDelete == head)
            {
                head = tmp;
            }
            delete toDelete;
        }
        return tmp->data;
    }

    void deleteList()
    {
        Node_C* tmp = head;
        if (head != nullptr)
        {
            do
            {
                Node_C* nextNode = tmp->next;
                delete tmp;
                tmp = nextNode;
            } while (tmp != head);

            head = nullptr;
        }
    }
};


int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    int lenList, DelInd_K;
    inputFile >> lenList >> DelInd_K;
    ListFull_C list;

    for (int data = 1; data <= lenList; data++)
    {
        list.pushTailCycle(data);
    }

    int answer = list.Del_K(DelInd_K);
    outputFile << answer;

    list.deleteList();
    outputFile.close();
    return 0;
}