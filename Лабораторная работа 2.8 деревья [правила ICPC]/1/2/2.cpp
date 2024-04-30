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

    int heightTree(Node* node)
    {
        if (node == nullptr) { return 0; }
        else
        {
            int leftHeight = heightTree(node->left);
            int rightHeight = heightTree(node->right); 

            int height = std::max(leftHeight, rightHeight) + 1;
            return height;
        }
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
        int height = heightTree(root);
        outputFile << height - 1;
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