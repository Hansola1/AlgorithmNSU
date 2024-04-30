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
    Tree() : root(nullptr) {}

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

    int countElemYesParents(Node* node, const int& level, int elemYesParents = 0)
    {
        if (node == nullptr) { return 0; }
        if (elemYesParents == level)
        {
            return 1;
        }

        return countElemYesParents(node->left, level, elemYesParents + 1) + countElemYesParents(node->right, level, elemYesParents + 1);
    }

    void buildTree(const std::vector<int>& numbers)
    {
        for (int num : numbers)
        {
            root = push(root, num);
        }
    }

    void printResult(int level, std::ofstream& outputFile)
    {
        int elemYesParents = countElemYesParents(root, level);
        outputFile << elemYesParents;
    }
};

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    int level, number;
    inputFile >> level;

    std::vector<int> numbers;
    while (inputFile >> number)
    {
        numbers.push_back(number);
    }
    Tree tree;
    tree.buildTree(numbers);
    tree.printResult(level, outputFile);

    inputFile.close();
    outputFile.close();

    return 0;
}