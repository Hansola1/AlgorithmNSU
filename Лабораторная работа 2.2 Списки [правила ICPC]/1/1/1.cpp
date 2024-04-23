#include <iostream>
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
//void pushHead(int data, Node_C*& head)  !!!


int CountNegativeNum(ListFull_C data)
{
	int count = 0;
	Node_C* tmp = data.head;

	while (tmp != nullptr)
	{
		if (tmp->data < 0 && tmp->data % 7 == 0)
		{
			count++;
		}
		tmp = tmp->next;
	}
	return count;
}

int main()
{
	int data;
	ListFull_C list;

	while (std::cin >> data)
	{
		list.pushHead(data);
	}

	int answer = CountNegativeNum(list);
	std::cout << answer << std::endl;

	list.deleteList();
	return 0;
}