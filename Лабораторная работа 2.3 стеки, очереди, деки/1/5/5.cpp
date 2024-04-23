#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

class Node_C {
public:
    double data;
    Node_C* next;
    Node_C(double data)
    {
        this->data = data;
        this->next = nullptr;
    }
};
class ListFullStack_C {
public:
    Node_C* head = nullptr;
    Node_C* tail = nullptr;

    void pushHead(double data)
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
    if (aStr == '~') return 5; // Унарный минус!!!
    return 0;
}

void InfixInPostfix(std::string& expressionInfix, std::string& expressionInPostfix)
{
    ListFullStack_C* stac = new ListFullStack_C;
    for (int i = 0; i < expressionInfix.size(); i++)
    {
        if (expressionInfix[i] >= '0' && expressionInfix[i] <= '9')
        {
            expressionInPostfix += expressionInfix[i];
        }
        else if (expressionInfix[i] == '(')
        {
            stac->pushHead(expressionInfix[i]);
        }
        else if (expressionInfix[i] == ')')
        {
            while (stac->head != nullptr && stac->head->data != '(')
            {
                expressionInPostfix += ' ';
                expressionInPostfix += stac->head->data;
                stac->pop();
            }
            stac->pop();
        }
        else
        {
            while (stac->head != nullptr && priority(expressionInfix[i]) <= priority(stac->head->data))
            {
                expressionInPostfix += ' ';
                expressionInPostfix += stac->head->data;
                stac->pop();
            }

            if (i == 0 || expressionInfix[i - 1] == '(')
            {
                stac->pushHead('~');
            }
            else
            {
                stac->pushHead(expressionInfix[i]);
            }
            expressionInPostfix += ' ';
        }
    }
    while (stac->head != nullptr)
    {
        expressionInPostfix += ' ';
        expressionInPostfix += stac->head->data;
        stac->pop();
    }
    stac->deleteList();
}

double calculationForPostfix(std::string& expressionInfix)
{
    ListFullStack_C* stac = new ListFullStack_C;
    std::string expressionPostfix, elemInStr;
    std::vector<std::string> strPostfixSplitted;

    InfixInPostfix(expressionInfix, expressionPostfix);
    std::istringstream oss(expressionPostfix);
    while (oss >> elemInStr)
    {
        strPostfixSplitted.push_back(elemInStr);
    }

    for (std::string separateNum : strPostfixSplitted)
    {
        if (separateNum[0] >= '0' && separateNum[0] <= '9')
        {
            stac->pushHead(std::stod(separateNum)); // queue->pushHead(i - '0'); stoi?
        }
        else
        {
            double operand2 = stac->head->data;
            stac->pop();
            double operand1 = 0;

            if (separateNum == "~")
            {
                stac->pushHead(0 - operand2);
                continue;
            }

            operand1 = stac->head->data;
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
    double answer = stac->head->data;
    stac->deleteList();
    return answer;
}

int main()
{
    std::string expressionInfix;
    std::ifstream inputFile("input.txt");
    char whitespace;

    while (inputFile.get(whitespace))
    {
        if (whitespace == '\n' || whitespace == '\0')
        {
            break;
        }
        if (whitespace != ' ')
        {
            expressionInfix += whitespace;
        }
    }
    double answer = calculationForPostfix(expressionInfix);
    std::cout << std::fixed << std::setprecision(20) << answer;
    return 0;
}