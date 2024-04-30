#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int data) : data(data), left(nullptr), right(nullptr) {}
};

class Tree {
public:
    Node* root;
    int listCount;
    Tree() : root(nullptr), listCount(0) {}

    Node* push(Node* node, int data)
    {
        if (node == nullptr) { return new Node(data); }
        if (data == node->data) { return node; }

        if (data < node->data)
        {
            node->left = push(node->left, data);
        }
        else
        {
            node->right = push(node->right, data);
        }
        return node;
    }

    void countList(Node* node)
    {
        if (node == nullptr) { return; }
        if (node->left == nullptr && node->right == nullptr)
        {
            listCount++;
        }

        countList(node->left);
        countList(node->right);
    }

    void buildTree(const std::vector<int>& numbers)
    {
        for (int num : numbers)
        {
            root = push(root, num);
        }
    }

    void printResult(std::ofstream& outputFile)
    {
        countList(root);
        outputFile << listCount;
    }
};

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    std::vector<int> numbers;
    int number;
    while (inputFile >> number)
    {
        numbers.push_back(number);
    }
    Tree tree;
    tree.buildTree(numbers);
    tree.printResult(outputFile);

    inputFile.close();
    outputFile.close();

    return 0;
}
