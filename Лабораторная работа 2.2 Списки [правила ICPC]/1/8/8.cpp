#include <iostream>
#include <fstream>
#include <string>
#include <list>

class Node_C {
public:
	std::string data;
	Node_C* next;

	Node_C(std::string data)
	{
		this->data = data;
		this->next = nullptr;
	}
};

class ListFull_C {
public:
	Node_C* head = nullptr;
	Node_C* tail = nullptr;

	void pushTail(std::string data)
	{
		Node_C* list = new Node_C(data);

		if (head == nullptr)
		{
			head = list;
		}
		if (tail != nullptr)
		{
			tail->next = list;
		}
		tail = list;
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

	int num, key; const int lenLists = 1000001;
	ListFull_C* lists = new ListFull_C[lenLists];
	std::string str;

	inputFile >> num;
	for (int i = 0; i < num; i++)
	{
		inputFile >> key >> str;
		lists[key].pushTail(str);
	}

	for (int i = 0; i < lenLists; i++)
	{
		Node_C* start = lists[i].head;
		while (start != nullptr)
		{
			outputFile << i << " " << start->data << std::endl;
			start = start->next;
		}
		lists[i].deleteList();
	}

	outputFile.close();
	return 0;
}