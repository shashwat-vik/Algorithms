#include <cstdio>
using namespace std;

void swap(int &a, int &b) { int temp = a; a = b; b = temp; }

class MaxHeap
{
private:
	int* arr;
	int length;
	int heap_size;
public:
	MaxHeap(int* a, int l) { arr = a, length = l; }

	void maxHeapify(int i)
	{
		int l = 2 * i + 1;
		int r = 2 * i + 2;
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
	void buildMaxHeap()
	{
		heap_size = length;
		for (int i = length / 2 - 1; i >= 0; --i)
			maxHeapify(i);
	}
	void heapSort()
	{
		buildMaxHeap();
		for (int i = length - 1; i >= 0; --i) {
			swap(arr[0], arr[i]);
			heap_size--;
			maxHeapify(0);
		}
	}

	void display()
	{
		printf("[%d", arr[0]);
		for (int i = 1; i < length; ++i)
			printf(", %d", arr[i]);
		printf("]\n");
	}
};

int main()
{
	int arr[7] = { 5, 6, 7, 1, 2, 4, 3 };
	MaxHeap H(arr, 7);
	H.display();
	H.heapSort();
	H.display();

	return 0;
}
