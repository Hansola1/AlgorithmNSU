#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

class Node {
public:
    char data;
    Node* left;
    Node* right;

    Node(char data) : data(data), left(nullptr), right(nullptr) {}
};
 
class Tree {
public: // р
    Node* root;
    Tree() : root(nullptr) {} //рр

    Node* pushDigit(const std::vector<char>& data, int& index)
    {
        if (isdigit(data[index])) { return new Node(data[index]); } //if (node == nullptr) { return new Node(data); }

        Node* node = new Node(data[index]);
        index++;

        node->left = pushDigit(data, index);
        index++;

        node->right = pushDigit(data, index);
        return node;
    }

    int calculationAllElement(Node* node, std::ofstream& outputFile)
    {
        if (isdigit(node->data)) { return node->data - '0'; }

        int left = calculationAllElement(node->left, outputFile);
        int right = calculationAllElement(node->right, outputFile);

        if (node->data == '-') { return left - right; }
        if (node->data == '+') { return left + right; }
        if (node->data == '*') { return left * right; }

        if (node->data == '/')
        {
            if (right == 0)
            {
                outputFile << "NO" << std::endl;
                exit(0); //return 0;  
            }
        }
        return left / right;
    }

    void printResult(std::ofstream& outputFile)
    {
        int answer = calculationAllElement(root, outputFile);
        outputFile << answer;
    }
};

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    char word; int index = 0;
    std::vector<char> str;
    while (inputFile >> word)
    {
        str.push_back(word);
    }
    Tree tree;
    tree.root = tree.pushDigit(str, index);
    tree.printResult(outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}