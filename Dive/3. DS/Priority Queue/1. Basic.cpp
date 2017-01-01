#include<cstdio>
#include <limits>
using namespace std;

void swap(int &x, int &y) { int temp = x; x = y; y = temp; }

class MinHeap
{
private:
	int *harr;
	int capacity;
	int heap_size;
public:
	MinHeap(int);

	int parent(int i) { return (i - 1) / 2; }
	int left(int i) { return 2 * i + 1; }
	int right(int i) { return 2 * i + 2; }

	int getMin() { return harr[0]; }
	int getSize() { return heap_size; }

	void heapifyUp(int);
	void heapifyDown(int);
	void deleteKey(int);
	void insertKey(int);
	int extractMin();

	void printArray() {
		for (int i = 0; i < heap_size; ++i)
			printf("%d ", harr[i]);
		printf("\n");
	}
};

MinHeap::MinHeap(int cap)
{
	this->capacity = cap;
	harr = new int[cap]();
	this->heap_size = 0;
}
void MinHeap::heapifyUp(int i)
{
	while (i != 0 && harr[i] < harr[parent(i)]) {
		swap(harr[i], harr[parent(i)]);
		i = parent(i);
	}
}
void MinHeap::heapifyDown(int i)
{
	int l = left(i), r = right(i);
	int smallest = i;
	if (l < heap_size && harr[l] < harr[i])
		smallest = l;
	if (r < heap_size && harr[r] < harr[smallest])
		smallest = r;
	if (smallest != i) {
		swap(harr[i], harr[smallest]);
		heapifyDown(smallest);
	}
}
void MinHeap::deleteKey(int k)
{
	if (heap_size == 0) {
		printf("ERROR : HEAP EMPTY\n");
		return;
	}

	harr[k] = harr[heap_size - 1];
	heap_size--;
	heapifyDown(k);
}
void MinHeap::insertKey(int k)
{
	if (heap_size == capacity) {
		printf("OVERFLOW : CAPACITY FULL\n");
		return;
	}

	heap_size++;
	harr[heap_size - 1] = k;
	heapifyUp(heap_size - 1);
}
int MinHeap::extractMin()
{
	if (heap_size == 0) {
		printf("HEAP EMPTY\n");
		return numeric_limits<int>::max();
	}
	else if (heap_size == 1) {
		heap_size--;
		return harr[0];
	}

	int min = harr[0];
	deleteKey(0);
	return min;
}
