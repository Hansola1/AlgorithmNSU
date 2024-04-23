#include <iostream>
#include <vector>

class Heap {
public:
    std::vector<int> heap;

    void push(int data)
    {
        heap.push_back(data); 
        int index = heap.size() - 1; 

        while (index > 0 && heap[index] < heap[(index - 1) / 2])
        {
            std::swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;   
        }
    }

    void pop()
    {
        if (heap.empty())
        {
            std::cout << "Heap is empty" << std::endl;
            return;
        }

        else 
        {
            int top = heap[0];
            std::swap(heap[0], heap.back());
            heap.pop_back(); 

            int index = 0;
            while (true) // перестройка кучи, после удаления. heapyfy
            {
                int left = 2 * index + 1;
                int right = 2 * index + 2;
                int smallest = index;

                if (left < heap.size() && heap[left] < heap[smallest])
                {
                    smallest = left;
                }
                if (right < heap.size() && heap[right] < heap[smallest])
                {
                    smallest = right;
                }

                if (smallest == index)
                {
                    break;
                }
                std::swap(heap[index], heap[smallest]);
                index = smallest;
            }
            std::cout << top << std::endl;
        }
    }
};

int main()
{
    int operations; std::cin >> operations;
    Heap heap;

    for (int i = 0; i < operations; i++)
    {
        std::string operation;
        std::cin >> operation;

        if (operation == "push")
        {
            int data;
            std::cin >> data;
            heap.push(data);
        }
        else if (operation == "pop")
        {
            heap.pop();
        }
    }
    return 0;
}