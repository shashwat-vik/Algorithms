#include <cstdio>
#include <list>
#include <limits>
using namespace std;

class Node
{
public:
	int v;
	int weight;
	Node(int v, int w) { this->v = v; this->weight = w; }
};

class Graph
{
private:
	int nV;
	list<Node> *adj;
public:
	Graph(int nV)
	{
		this->nV = nV;
		adj = new list<Node>[nV];
	}
	void addEdge(int u, int v, int w)
	{
		adj[u].push_back(Node(v, w)); adj[v].push_back(Node(u, w));
	}

	void Dijkshtra(int src)
	{
		int curr_n = src;
		bool *explored = new bool[this->nV]();
		int *distance = new int[this->nV];
		int *parent = new int[this->nV];
		for (int i = 0; i < this->nV; ++i)
			distance[i] = numeric_limits<int>::max(), parent[i] = -1;

		int dist_n, min; list<Node>::iterator p;
		distance[curr_n] = 0;

		while (!explored[curr_n]) {
			// UPDATE MIN DISTANCE TO ADJACENT NODES FROM CURRENT NODE (curr_n)
			for (p = adj[curr_n].begin(); p != adj[curr_n].end(); ++p) {
				dist_n = distance[curr_n] + p->weight;
				if (dist_n < distance[p->v]) {
					distance[p->v] = dist_n;
					parent[p->v] = curr_n;
				}
			}
			explored[curr_n] = true;

			// FIND MIN DISTANCE THAT IS NOT EXPLORED
			min = numeric_limits<int>::max();
			for (int i = 0; i < this->nV; ++i) {
				if (!explored[i] && min > distance[i])
					min = distance[i], curr_n = i;
			}
		}
		// DISPLAY INFO
		this->display_info(src, parent, distance);
	}

	// DISPLAY INFO
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

	G.Dijkshtra(1);

	return 0;
}
