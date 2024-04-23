#include <iostream>
#include <fstream>
#include <list>

class Node_C {
public:
	int data;
	Node_C* next;

	Node_C(int data)
	{
		this->data = data;
		this->next = nullptr;
	}
};

class ListFull_C {
public:
	Node_C* head = nullptr;
	Node_C* tail = nullptr;

	void pushHead(int data) 
	{
		Node_C* node = new Node_C(data);
		node->next = head;
		head = node;

		if (node->next == nullptr)
		{
			tail = head;
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

void NumDetective(ListFull_C& data, int num)
{
	Node_C* tmp = data.head; 
	Node_C* backData = nullptr; 

	while (tmp != nullptr && tmp->next != nullptr) 
	{
		Node_C* toDelete = tmp;
		if (tmp->next->data == num)
		{
			tmp = tmp->next; 
			if (toDelete == data.head)
			{
				data.head = tmp; 
				delete toDelete;
			}
			else
			{
				backData->next = tmp; 
				delete toDelete; 
			}
		}

		else
		{
			backData = tmp;
			tmp = tmp->next;
		}
	}
}

int main()
{
	std::ifstream inputFile("input.txt");
	std::ofstream outputFile("output.txt");

	int num, data;
	ListFull_C list;
	
	inputFile >> num;
	while (inputFile >> data)
	{
		list.pushHead(data); 
	}

	NumDetective(list, num);
	Node_C* newList = list.head;
	while (newList != nullptr)
	{
		outputFile << newList->data << ' ';
		newList = newList->next;
	}

	list.deleteList();
	outputFile.close();
	return 0;
}