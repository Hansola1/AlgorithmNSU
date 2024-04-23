#include <iostream>
#include <fstream>
#include <string>

class MyBuffer {
public:
	int maxSize, *arr, size, begin, end;
	
public:
	MyBuffer(int maxSize) : maxSize(maxSize), arr(new int[maxSize]), size(0), begin(0), end(0) { };
	
	int getSize() {
		return size;
	}
	
	bool push_back(int val) {
		if (size >= maxSize)
			return 0;
			
		if (size == 0) {
			begin = end = 0;
			arr[end] = val;
			size++;
			return 1;
		}
		
		int ind = (++end) % maxSize;
		arr[ind] = val;
		size++;
		return 1;
	}
	
	int top() {
		return arr[begin];
	}
	
	void pop_front() {
		begin++;
		begin %= maxSize;
		size--;
	}
};

int main() {
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	int N, M;
	in >> N >> M;
	
	MyBuffer *buffer = new MyBuffer(N);
	
	int last;
	while (in >> last) {
		if (last >= 0) {
			for (int i = 0; i < last; i++) {
				int lastNum;
				in >> lastNum;
				if (!buffer->push_back(lastNum)) {
					out << "Memory overflow\n";
					for ( ; i < last-1; i++)
						in >> lastNum;
					break;
				}
			}
		}
		else {
			last = -last;
			int sum = 0;
			bool isSuccessfully = 1;
			for (int i = 0; i < last; i++) {
				if (!buffer->getSize()) {
					out << (i ? std::to_string(sum/i) + '\n' : "") << "Empty queue\n";
					isSuccessfully = 0;
					break;
				}
				int lastNum = buffer->top();
				buffer->pop_front();
				sum += lastNum;
			}
			if (isSuccessfully)
				out << (sum/last) << '\n';
		}
	}
	in.close();
	out.close();
	return 0;
}