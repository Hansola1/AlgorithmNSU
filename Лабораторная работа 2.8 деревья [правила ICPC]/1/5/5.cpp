#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

class Node {
public:
    std::string data;
    Node* left;
    Node* right;

    Node(std::string data) : data(data), left(nullptr), right(nullptr) {}
};

class Tree {
public:
    Node* root;
    Tree() : root(nullptr) {}

    Node* push(Node* node, std::string data)
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

    void inside(Node* node, std::ofstream& outputFile)
    {
        if (node == nullptr) { return; }

        inside(node->left, outputFile);
        outputFile << node->data << std::endl;
        inside(node->right, outputFile);
    }

    void buildTree(std::vector<std::string>& str)
    {
        for (const auto& s : str)
        {
            root = push(root, s);
        }
    }

    void printResult(std::ofstream& outputFile)
    {
        inside(root, outputFile);
    }
};

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    std::string word;
    std::vector<std::string> str;
    while (inputFile >> word)
    {
        str.push_back(word);
    }
    Tree tree;
    tree.buildTree(str);
    tree.printResult(outputFile);

    inputFile.close();
    outputFile.close();

    return 0;
}
