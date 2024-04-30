#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

class Node {
public:
    char data; //std::string data;
    Node* left;
    Node* right;

    Node(char data) : data(data), left(nullptr), right(nullptr) {}
};

class Tree {
public:
    Node* root;
    Tree() : root(nullptr) {}

    Node* push(Node* node, char data)//std::string data)
    {
        if (node == nullptr) { return new Node(data); }

        if (data <= node->data)
        {
            node->left = push(node->left, data);
        }
        else
        {
            node->right = push(node->right, data);
        }
        return node;
    }
    void buildTree(std::vector<std::string>& str)
    {
        for (int i = str.size() - 1; i >= 0; i--) //for (const auto& s : str)
        {
            for (char s : str[i])
            {
                root = push(root, s);
            }
        }
    }

    void directTraversal(Node* node, std::ofstream& outfile)
    {
        if (node == nullptr) { return; }

        outfile << node->data;
        directTraversal(node->left, outfile);
        directTraversal(node->right, outfile);
    }

    void printResult(std::ofstream& outputFile)
    {
        directTraversal(root, outputFile);
        outputFile << std::endl;
    }
};

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    std::string strPattern;
    std::vector<std::string> str;
    while (inputFile >> strPattern)
    {
        str.push_back(strPattern);
    }
    Tree tree;
    tree.buildTree(str);
    tree.printResult(outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}
