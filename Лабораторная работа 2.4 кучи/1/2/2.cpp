#include <iostream>
#include <fstream>
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

    int pop()
    {
        if (heap.empty())
        {
            return -1;
        }
        int top = heap[0];
        std::swap(heap[0], heap.back());
        heap.pop_back();

        int index = 0;
        while (true)
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
        return top;
    }

    void HeapSortBin(long a[], int n)
    {
        for (int i = 0; i < n; i++)
        {
            push(a[i]);
        }

        for (int i = 0; i < n; i++)
        {
            a[i] = pop(); 

        }
    }
};

int main()
{
    std::ifstream inputFile("input.bin", std::ios::binary);
    std::ofstream outputFile("output.bin", std::ios::out | std::ios::binary);
    long len; 
    inputFile.read(reinterpret_cast<char*>(&len), sizeof(long));

    long* arr = new long[len];
    for (int i = 0; i < len; i++)
    {
        inputFile.read(reinterpret_cast<char*>(&arr[i]), sizeof(long));
    }

    Heap heap;
    heap.HeapSortBin(arr, len);
    for (int i = 0; i < len; i++)
    {
        outputFile.write(reinterpret_cast<char*>(&arr[i]), sizeof(long));
    }

    outputFile.close();
    delete[] arr;
    return 0;
}