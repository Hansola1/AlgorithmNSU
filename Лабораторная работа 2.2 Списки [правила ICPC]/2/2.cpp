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
		Node_C* node = new Node_C(data);
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

int arithmeticMean(ListFull_C data)
{
	int count = 0, sum = 0;
	Node_C* tmp = data.head;

	while (tmp != nullptr)
	{
		sum = sum + tmp->data;
		count++;

		tmp = tmp->next;
	}
	int mean = sum / count;
	return mean;
}

int main()
{
	std::ifstream inputFile("input.txt");
	std::ofstream outputFile("output.txt");

	int data; 
	ListFull_C list; 

	while (inputFile >> data)
	{
		list.pushTail(data);
	}

	int answer = arithmeticMean(list);
	outputFile << answer << std::endl;

	list.deleteList();
	outputFile.close();
	return 0;
}