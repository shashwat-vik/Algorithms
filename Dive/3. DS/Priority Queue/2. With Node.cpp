#include <cstdio>
#include <limits>
using namespace std;

class Node
{
public:
	int key;
	int value;
	Node(int k, int v) { key = k; value = v; }
};

void swap(Node **a, Node **b) { Node *c = *a;  *a = *b; *b = c; }

class MinHeap
{
private:
	int capacity;
	int heap_size;
	Node **harr;
public:
	MinHeap(int cap)
	{
		capacity = cap;
		heap_size = 0;
		harr = new Node*[cap];
	}

	int parent(int i) { return (i - 1) / 2; }
	int left(int i) { return 2 * i + 1; };
	int right(int i) { return 2 * i + 2; }
	Node* getMinNode() { return harr[0]; }
	int getSize() { return heap_size; }

	void heapifyUp(int);
	void heapifyDown(int);
	void insertNode(int, int);
	void deleteByIdx(int);
	int extractMin();

	void printHeap();
};

void MinHeap::heapifyUp(int i)
{
	while (i != 0 && harr[i]->key < harr[parent(i)]->key) {
		swap(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}
void MinHeap::heapifyDown(int i)
{
	int l = left(i), r = right(i);
	int smallest = i;
	if (l < heap_size && harr[l]->key < harr[smallest]->key)
		smallest = l;
	if (r < heap_size && harr[r]->key < harr[smallest]->key)
		smallest = r;
	if (smallest != i) {
		swap(&harr[i], &harr[smallest]);
		heapifyDown(smallest);
	}
}
void MinHeap::insertNode(int key, int value)
{
	if (heap_size == capacity) {
		printf("ERROR: OVERFLOW\n");
		return;
	}

	heap_size++;
	harr[heap_size - 1] = new Node(key, value);
	heapifyUp(heap_size - 1);
}
void MinHeap::deleteByIdx(int idx)
{
	if (heap_size == 0) {
		printf("ERROR: HEAP EMPTY\n");
		return;
	}

	harr[idx] = harr[heap_size - 1];
	heap_size--;
	heapifyDown(idx);
}
int MinHeap::extractMin()
{
	if (heap_size == 0) {
		printf("ERROR: HEAP EMPTY\n");
		return numeric_limits<int>::max();
	}

	int val = harr[0]->value;
	deleteByIdx(0);
	return val;
}

void MinHeap::printHeap()
{
	for (int i = 0; i < heap_size; ++i)
		printf("%d(%d) ", harr[i]->key, harr[i]->value);
	printf("\n");
}
