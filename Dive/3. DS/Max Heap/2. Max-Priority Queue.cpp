#include <iostream>
using namespace std;

void swap(int &a, int &b) { int temp = a; a = b; b = temp; }

class MaxPriorityQ
{
private:
	int* arr;
	int length;
	int heap_size;
public:
	MaxPriorityQ(int* a, int l) { arr = a; length = l; heap_size = 0; }

	int left(int i) { return 2 * i + 1; }
	int right(int i) { return 2 * i + 2; }
	int parent(int i) { return (i - 1) / 2; }

	int heapMaximum() { return arr[0]; }
	void maxHeapify(int);
	int extractMax();
	void increaseKey(int, int);
	void heapInsert(int);
};

void MaxPriorityQ::maxHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int largest = i;
	if (l < heap_size && arr[l] > arr[largest])
		largest = l;
	if (r < heap_size && arr[r] > arr[largest])
		largest = r;
	if (i != largest) {
		swap(arr[i], arr[largest]);
		maxHeapify(largest);
	}
}
int MaxPriorityQ::extractMax()
{
	if (heap_size < 1) {	//  ERROR : Heap Underflow
		cout << "ERROR : Heap Underflow" << endl;
		return numeric_limits<int>::max();
	}
	int val = arr[0];
	arr[0] = arr[heap_size - 1];
	heap_size--;
	maxHeapify(0);
	return val;
}
void MaxPriorityQ::increaseKey(int i, int k)
{
	if (arr[i] > k) {	// ERROR : Key(k) smaller than current key(arr[i])
		cout << "ERROR : Key(k) smaller than current key(arr[i])" << endl;
		return;
	}

	arr[i] = k;
	while (i > 0 && arr[parent(i)] < arr[i]) {
		swap(arr[i], arr[parent(i)]);
		i = parent(i);
	}
}
void MaxPriorityQ::heapInsert(int k)
{
	if (heap_size == length) {	// ERROR : Heap Overflow
		cout << "ERROR : Heap Overflow" << endl;
		return;
	}
	heap_size++;
	arr[heap_size - 1] = numeric_limits<int>::min();
	increaseKey(heap_size - 1, k);
}

int main()
{
	int arr[10];
	MaxPriorityQ M(arr, 10);
	M.heapInsert(5);
	M.heapInsert(-1);
	M.heapInsert(2);
	M.heapInsert(10);
	M.heapInsert(0);

	int n = 5;
	while(n--)
		cout << M.extractMax() << endl;
}
