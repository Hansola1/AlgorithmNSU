#include <iostream>
#include <fstream>
#include <string>
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

	bool dublicbublic(int data) 
	{
		Node_C* dublic = head;
		while (dublic != nullptr) 
		{
			if (dublic->data == data)
			{
				return 1;
			}
			dublic = dublic->next;
		}
		return 0;
	}

	void pushIncreasing(int data)
	{
		Node_C* newNode = new Node_C(data);	
		if (!dublicbublic(data))
		{
			if (head == nullptr || data < head->data)
			{
				newNode->next = head; 
				head = newNode; 
			}

			else
			{
				Node_C* tmp = head;
				while (tmp->next != nullptr && tmp->next->data < data)
				{
					tmp = tmp->next;
				}
				newNode->next = tmp->next; 
				tmp->next = newNode;  
			}
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

int main()
{
	std::ifstream inputFile("input.txt");
	std::ofstream outputFile("output.txt");

	int data;
	ListFull_C list;
	while (inputFile >> data)
	{
		list.pushIncreasing(data);
	}

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