#include <cstdio>
#include <limits>
#include <map>
#include <list>
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
	map<int, int> m_pos;
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
	int getIdx(int value) { return m_pos[value]; }

	void heapifyUp(int);
	void heapifyDown(int);
	void insertNode(int, int);
	void deleteByIdx(int);
	void deleteByVal(int);
	int extractMin();
	bool checkPresence(int v) { return (m_pos[v] < heap_size); }

	void printHeap();
	void printPos();
};

void MinHeap::heapifyUp(int i)
{
	while (i != 0 && harr[i]->key < harr[parent(i)]->key) {
		m_pos[harr[i]->value] = parent(i);
		m_pos[harr[parent(i)]->value] = i;
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
		m_pos[harr[i]->value] = smallest;
		m_pos[harr[smallest]->value] = i;
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
	m_pos[value] = heap_size - 1;
	heapifyUp(heap_size - 1);
}
void MinHeap::deleteByIdx(int idx)
{
	if (heap_size == 0) {
		printf("ERROR: HEAP EMPTY\n");
		return;
	}

	harr[idx] = harr[heap_size - 1];
	m_pos[harr[heap_size - 1]->value] = idx;
	heap_size--;
	heapifyDown(idx);
}
void MinHeap::deleteByVal(int val) { deleteByIdx(m_pos[val]); }
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
void MinHeap::printPos()
{
	for (int i = 0; i < heap_size; ++i)
		printf("   ## %d at idx=%d\n", harr[i]->value, m_pos[harr[i]->value]);
	printf("\n");
}

class GNode
{
public:
	int v;
	int weight;
	GNode(int v, int w) { this->v = v; this->weight = w; }
};
class Graph
{
private:
	int nV;
	list<GNode> *adj;
public:
	Graph(int nV) { this->nV = nV; adj = new list<GNode>[nV]; }
	void addEdge(int u, int v, int weight) { adj[u].push_back(GNode(v, weight)); }

	void Dijkshra(int u)
	{
		MinHeap H(nV);
		int src = u;
		int *distance = new int[nV];
		int *parent = new int[nV];

		for (int i = 0; i < nV; ++i) {
			if (i == u) {
				H.insertNode(0, i);
				distance[i] = 0;
			}
			else {
				H.insertNode(numeric_limits<int>::max(), i);
				distance[i] = numeric_limits<int>::max();
			}
			parent[i] = -1;
		}

		int n_dist;
		list<GNode>::iterator p;
		while (H.getSize() != 0) {
			u = H.extractMin();
			for (p = adj[u].begin(); p != adj[u].end() && H.checkPresence(p->v); ++p) {
				n_dist = distance[u] + p->weight;
				if (n_dist < distance[p->v]) {
					distance[p->v] = n_dist;
					H.deleteByVal(p->v);
					H.insertNode(n_dist, p->v);
					parent[p->v] = u;
				}
			}
		}
		display_info(src, parent, distance);
	}

	void display_info(int src, int *parent, int *distance)
	{
		for (int i = 0; i < this->nV; ++i) {
			printf("INDEX %d\n", i);
			printf("DISTANCE : %d\n", distance[i]);
			printf("PATH : ");
			this->path(src, i, parent);
			printf("\n\n");
		}
	}
	void path(int src, int curr_v, int *parent)
	{
		if (curr_v == src) {
			printf("%d", curr_v);
			return;
		}
		path(src, parent[curr_v], parent);
		printf(" --> %d", curr_v);
	}
};
int main()
{
	Graph G(9);

	G.addEdge(0, 1, 4);
	G.addEdge(0, 7, 8);
	G.addEdge(1, 0, 4);
	G.addEdge(1, 2, 8);
	G.addEdge(1, 7, 11);
	G.addEdge(2, 1, 8);
	G.addEdge(2, 3, 7);
	G.addEdge(2, 5, 4);
	G.addEdge(2, 8, 2);
	G.addEdge(3, 2, 7);
	G.addEdge(3, 4, 9);
	G.addEdge(3, 5, 14);
	G.addEdge(4, 3, 9);
	G.addEdge(4, 5, 10);
	G.addEdge(5, 2, 4);
	G.addEdge(5, 4, 10);
	G.addEdge(5, 6, 2);
	G.addEdge(6, 3, 14);
	G.addEdge(6, 5, 2);
	G.addEdge(6, 7, 1);
	G.addEdge(6, 8, 6);
	G.addEdge(7, 0, 8);
	G.addEdge(7, 1, 11);
	G.addEdge(7, 6, 1);
	G.addEdge(7, 8, 7);
	G.addEdge(8, 2, 2);
	G.addEdge(8, 6, 6);
	G.addEdge(8, 7, 7);

	G.Dijkshra(1);
}
