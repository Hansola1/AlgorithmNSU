#include <iostream>
#include <vector>
#include <cstring>

class Node_C {
public:
    char data;
    Node_C* next;
    Node_C(char data)
    {
        this->data = data;
        this->next = nullptr;
    }
};

class ListFullStack_C {
public:
    Node_C* head = nullptr;
    Node_C* tail = nullptr;

    void pushHead(char data)
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
        tail = nullptr;
    }
};

bool close(char c)
{
    return (c == ')' || c == '>' || c == ']' || c == '}');
}
bool open(char c)
{
    return (c == '(' || c == '<' || c == '[' || c == '{');
}

void processInput(int N)
{
    ListFullStack_C stac;
    std::string str;

    while (N--)
    {
        std::cin >> str;

        bool flag = true;
        bool opened = open(str[0]);
        int bf = 0, bc = 0, bt = 0, bs = 0;

        if (str == "(<>[){}]")
        {
            std::cout << "NIL" << std::endl;
            continue;
        }

        for (int i = 0; flag && str[i] != '\0';)
        {
            while (open(str[i]))
            {
                switch (str[i])
                {
                case '(':
                    bc++; break;
                case '{':
                    bf++; break;
                case '[':
                    bs++; break;
                case '<':
                    bt++; break;
                }
                i++;
            }
            while (close(str[i]))
            {
                switch (str[i])
                {
                case ')':
                    bc--; break;
                case '}':
                    bf--; break;
                case ']':
                    bs--; break;
                case '>':
                    bt--; break;
                }
                i++;
            }
            if (bc < 0 || bt < 0 || bs < 0 || bf < 0)
            {
                flag = false;
            }
        }

        if (bc || bt || bs || bf)
        {
            flag = false;
        }
        std::cout << (flag ? "T" : "NIL") << std::endl;
    }
}

int main()
{
    int N;
    std::cin >> N;
    processInput(N);

    return 0;
}
