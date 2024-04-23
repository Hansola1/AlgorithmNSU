#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

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

class ListFullStack_C {
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
    void pop()
    {
        Node_C* tmp = head;
        head = head->next;
        delete tmp;

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
    }
};

int PostfixCalculations(std::string& strPostfix)
{
    ListFullStack_C* stac = new ListFullStack_C;

    std::vector<std::string> strPostfixSplitted;
    std::string elemInStr;
    std::istringstream oss(strPostfix);

    while (oss >> elemInStr) 
    {
        strPostfixSplitted.push_back(elemInStr);
    }
    for (std::string separateNum : strPostfixSplitted)
    {
        if (separateNum[0] >= '0' && separateNum[0] <= '9')
        {
            stac->pushHead(std::stoi(separateNum)); // stac->pushHead(i - '0');
        }
        else
        {
            int operand2 = stac->head->data;
            stac->pop();
            int operand1 = stac->head->data;
            stac->pop();

            if (separateNum == "+")
            {
                stac->pushHead(operand1 + operand2);
            }
            if (separateNum == "-")
            {
                stac->pushHead(operand1 - operand2);
            }
            if (separateNum == "*")
            {
                stac->pushHead(operand1 * operand2);
            }
            if (separateNum == "/")
            {
                stac->pushHead(operand1 / operand2);
            }
        }
    }
    // delete stac; //stac->deleteList();
    return stac->head->data;
}

int main()
{
    std::string strPostfix;
    std::getline(std::cin, strPostfix); //inputFile >> strPostfix;

    int answer = PostfixCalculations(strPostfix);
    std::cout << answer;
    return 0;
}