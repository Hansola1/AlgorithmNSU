#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>

class Node {
public:
    int data, count;
    Node* left;
    Node* right;

    Node(int data) : data(data), count(1), left(nullptr), right(nullptr) {}
};

class Tree {
public:
    Node* root;
    Tree() : root(nullptr) {}

    Node* push(Node* node, int data)
    {
        if (node == nullptr) { return new Node(data); }

        if (data < node->data)
        {
            node->left = push(node->left, data);
        }
        else if (data == node->data)
        {
            node->count++;
        }
        else
        {
            node->right = push(node->right, data);
        }
        return node;
    }

    void buildTree(const std::vector<int>& numbers)
    {
        for (int num : numbers)
        {
            root = push(root, num);
        }
    }

    void treeSort(Node* node, std::ofstream& outfile)
    {
        if (node == nullptr) { return; }
        treeSort(node->left, outfile);

        for (int i = 0; i < node->count; i++)
        {
            outfile.write(reinterpret_cast<const char*>(&node->data), sizeof(int));
        }
        treeSort(node->right, outfile);
    }

    /*void shuffle(std::vector<int>& numbers, int len)
    {
        srand(time(NULL));
        for (int i = len - 1; i >= 1; i--)
        {
            int j = rand() % i;
            std::swap(numbers[j], numbers[i]);
        }
    }*/

    void printResult(std::ofstream& outfile) {  treeSort(root, outfile);  }
};

int main()
{
    std::ifstream inputFile("input.bin", std::ios::binary);
    std::ofstream outputFile("output.txt", std::ios::binary);

    int len, number;
    inputFile.read(reinterpret_cast<char*>(&len), sizeof(int));

    std::vector<int> numbers;
    for (int i = 0; i < len; ++i)
    {
        inputFile.read(reinterpret_cast<char*>(&number), sizeof(int));
        numbers.push_back(number);
    }
    Tree tree;
    //tree.shuffle(numbers, len);
    tree.buildTree(numbers);
    tree.printResult(outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}
