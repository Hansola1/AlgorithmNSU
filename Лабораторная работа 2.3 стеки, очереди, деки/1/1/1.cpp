#include <iostream>
#include <fstream>

class Node_C {
public:
    char data;
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

int priority(char aStr)
{
    if (aStr == '(') return 1;
    if (aStr == ')') return 2;
    if (aStr == '+' || aStr == '-') return 3;
    if (aStr == '/' || aStr == '*') return 4;
    return 0;
}

void toPostfix(std::string& strInfix, std::string& strPostfix)
{
    ListFullStack_C* stac = new ListFullStack_C;
    // for (char i = 0; i < strInfix.length(); i++)
    for (char i : strInfix)
    {
        if (i > 96 && i < 123)
        {
            strPostfix += i;
        }

        else if (i == '(')
        {
            stac->pushHead(i);
        }

        else if (i == ')')
        {
            while (stac->head != nullptr && stac->head->data != '(')
            {
                strPostfix += stac->head->data;
                stac->pop();
            }
            stac->pop();
        }

        else  //strInfix[i] == '*' || strInfix[i] == '/' || strInfix[i] == '+' || strInfix[i] == '-'
        {
            while (stac->head != nullptr && priority(i) <= priority(stac->head->data))
            {
                strPostfix += stac->head->data;
                stac->pop();
            }
            stac->pushHead(i);
        }
    }

    while (stac->head != nullptr)
    {
        strPostfix += stac->head->data;
        stac->pop();
    }

    stac->deleteList();
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    std::string strInfix, strPostfix;
    inputFile >> strInfix;

    toPostfix(strInfix, strPostfix);
    outputFile << strPostfix;

    outputFile.close();
    return 0;
}