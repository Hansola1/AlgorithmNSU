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

	void pushTail(int data)
	{
		Node_C* node= new Node_C(data);

		if (head == nullptr)
		{
			head = node;
		}

		if (tail != nullptr)
		{
			tail->next = node;
		}
		tail = node;
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

int replayDetective(ListFull_C& data)
{
	Node_C* tmp = data.head; 
	while (tmp != nullptr && tmp->next != nullptr)
	{
		Node_C* replay = tmp->next; 

		if (tmp->data == replay->data) 
		{
			tmp->next = replay->next; 
			delete replay;
		}
		else
		{
			tmp = tmp->next;
		}
	}
	return tmp->data;
}

int main()
{
	std::ifstream inputFile("input.txt");
	std::ofstream outputFile("output.txt");

	int data; ListFull_C list;
	while (inputFile >> data)
	{
		list.pushTail(data); //!!!
	}
	int answer = replayDetective(list);

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