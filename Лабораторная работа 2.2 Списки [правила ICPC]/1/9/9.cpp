#include <iostream>
#include <fstream>
#include <list>
#include <ctime>

class NodeList_C {
public:
	int data, dist;
	NodeList_C* next;
	NodeList_C* nextBig;

	NodeList_C(int data)
	{
		this->data = data;
		this->dist = 0;
		this->next = nullptr;
		this->nextBig = nullptr;
	}
};

class ListFull_C {
public:
	NodeList_C* head = nullptr;
	NodeList_C* createList(int data)
	{
		NodeList_C* list = new NodeList_C(data);
		return list;
	}

	void deleteList()
	{
		NodeList_C* node = head;
		while (node != nullptr)
		{
			NodeList_C* tmp = node;
			node = node->next;
			delete tmp;
		}
	}
};

void addElement(NodeList_C** head, int index, int data) 
{
	NodeList_C* node = new NodeList_C(data);
	NodeList_C* list = (*head);
	NodeList_C* nodeBig = (*head);
	bool is_big = (rand() % 100 == 99) ? true : false;

	if (index == 0)
	{
		if (is_big) 
		{
			node->nextBig = *head;
			node->dist = 1;
		}
		else
		{
			node->nextBig = (*head)->nextBig;
			node->dist = (*head)->dist + 1;
			(*head)->dist = -1;
		}

		node->next = (*head);
		(*head) = node;
		return;
	}

	int c_ind = 0;
	while (c_ind + list->dist <= index && list->nextBig != nullptr) 
	{
		c_ind += list->dist;
		nodeBig = list;
		list = list->nextBig;
	}

	NodeList_C* cur_big = list;
	c_ind = index - c_ind;
	for (int j = 1; j < c_ind; ++j)
	{
		list = list->next;
	}

	if (c_ind == 0)
	{
		list = nodeBig;
		for (int j = 1; j < nodeBig->dist; ++j)
		{
			list = list->next;
		}

		if (is_big)
		{
			node->dist = 1;
			node->nextBig = cur_big;
			nodeBig->nextBig = node;
		}
		else 
		{
			nodeBig->dist++;
			node->dist = -1;
		}
		nodeBig = cur_big;
		list->next = node;
		return;
	}

	if (is_big)
	{
		if (cur_big->nextBig != nullptr) 
		{
			node->nextBig = cur_big->nextBig;
			node->dist = cur_big->dist - c_ind + 1;
		}
		else 
		{
			node->dist = 0;
			node->nextBig = nullptr;
		}
		cur_big->nextBig = node;
		cur_big->dist = c_ind;
	}
	else 
	{
		node->dist = -1;
		cur_big->dist++;
	}
	node->next = list->next;
	list->next = node;
}

int main()
{
	srand(static_cast<unsigned>(time(NULL)));
	int N, a, index, num;
	std::cin >> N >> a >> index >> num;

	ListFull_C list;
	NodeList_C* head = list.createList(num);
	for (int i = 1; i < N; i++)
	{
		std::cin >> a;
		if (a == 0)
		{
			std::cin >> index >> num;
			addElement(&head, index, num);
		}
		if (a == 1)
		{
			std::cin >> index;
			int cur_ind = 0;
			NodeList_C* list = head;

			while (cur_ind + list->dist <= index && list->nextBig != nullptr)
			{
				cur_ind += list->dist;
				list = list->nextBig;
			}
			cur_ind = index - cur_ind;
			for (int j = 0; j < cur_ind; j++)
			{
				list = list->next;
			}
			std::cout << list->data << std::endl;
		}
	}
	list.deleteList();
	return 0;
}