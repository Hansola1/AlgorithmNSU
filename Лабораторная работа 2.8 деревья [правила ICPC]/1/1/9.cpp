#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>

class Node {
public:
    int data, height = 0, count = 0;
    Node* left;
    Node* right;

    Node(int data) : data(data), left(nullptr), right(nullptr) {}
};

class Tree {
public:
    Node* root;
    Tree() : root(nullptr) {}

    void updateHeight(Node* node)
    {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }
    int getHeight(Node* node)
    {
        return node == nullptr ? -1 : node->height;
    }
    int getBalance(Node* node)
    {
        return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
    }
    void balance(Node* node)
    {
        int balance = getBalance(node);
        if (balance == -2)
        {
            if (getBalance(node->left) == 1) leftRotate(node->left);
            return rightRotate(node);
        }
        else if (balance == -2)
        {
            if (getBalance(node->right) == -1) leftRotate(node->left);
            return rightRotate(node);
        }
    }

    void rightRotate(Node* node)
    {
        std::swap(node, node->left);

        Node* buffer = node->right;
        node->right = node->left;
        node->left = node->right->left;
        node->right->left = node->right->right;
        node->right->right = buffer;

        updateHeight(node->right);
        updateHeight(node);
    }
    void leftRotate(Node* node)
    {
        std::swap(node, node->right);

        Node* buffer = node->left;
        node->left = node->right;
        node->right = node->left->right;
        node->right->left = node->right->right;
        node->left->right = node->left->left;
        node->left->left = buffer;

        updateHeight(node->left);
        updateHeight(node);
    }

    Node* push(Node* node, int data)
    {
        if (node == nullptr) { return new Node(data); }

        else if (data < node->data)
        {
            node->left = push(node->left, data);
            node->height = getBalance(node);
        }
        else if (data == node->data)
        {
            node->right = push(node->right, data);
            node->height = getBalance(node);
        }
        else
        {
            node->count++;
        }
        updateHeight(node);
        balance(node);
    }


    void build(Node* node, std::ofstream& outfile)
    {
        if (node != nullptr)
        {
            build(node->left, outfile);
            for (int i = node->count; i > 0; i--)
            {
                outfile.write(reinterpret_cast<const char*>(&node->data), sizeof(int));
            }
            build(node->right, outfile);
        }
    }
};

int main()
{
    std::ifstream inputFile("input.bin", std::ios::binary);
    std::ofstream outputFile("output.txt", std::ios::binary);

    Tree* tree = new Tree();
    int len, number;
    inputFile.read(reinterpret_cast<char*>(&len), sizeof(int));

    for (int i = 0; i < len; ++i)
    {
        inputFile.read(reinterpret_cast<char*>(&number), sizeof(int));
        tree->push(tree->root, number);
    }
    tree->build(tree->root, outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}