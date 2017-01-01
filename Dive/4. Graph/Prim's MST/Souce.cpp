#include<iostream>
#include<list>
#include<algorithm>
#include<cstdio>
using namespace std;

class Node
{
public:
	int v;
	int weight;
	Node(int v, int weight) { this->v = v, this->weight = weight; }
};
class Graph
{
private:
	int nV;
	list<Node>* adj;
	friend class Prim;
public:
	Graph(int nV)
	{
		this->nV = nV;
		adj = new list<Node>[this->nV];
	}
	~Graph() { delete[] adj; }

	void addEdge(int u, int v, int weight)
	{
		adj[u].push_back(Node(v, weight));
		adj[v].push_back(Node(u, weight));
	}
};

class Prim
{
private:
	const Graph &G;
	bool* mstSet;
	int* distance;
	int* parent;
	int src;
public:
	Prim(const Graph &_G, int src) : G(_G)
	{
		mstSet = new bool[G.nV]();
		distance = new int[G.nV];

		parent = new int[G.nV];
		fill_n(distance, G.nV, numeric_limits<int>::max());

		this->src = src;
	}
	~Prim() { delete[] mstSet, delete[] distance, delete[] parent; }

	void prim()
	{

		distance[src] = 0;
		parent[src] = -1;

		int min_distance, curr_v;
		list<Node>::iterator p;
		for (int count = 0; count < G.nV; ++count)
		{
			// FIND NEXT MIN NODE OUTSIDE THE MST-CUT
			min_distance = numeric_limits<int>::max();
			for (int i = 0; i < G.nV; ++i)
			{
				if (!mstSet[i] && (distance[i] < min_distance))
					min_distance = distance[i], curr_v = i;
			}

			mstSet[curr_v] = true;

			// INCLUDE NODE IN THE CUT AND EXPLORE IT'S NEIGHBOURS
			for (p = G.adj[curr_v].begin(); p != G.adj[curr_v].end(); ++p)
			{
				if (!mstSet[p->v] && (distance[p->v] > p->weight))
					distance[p->v] = p->weight, parent[p->v] = curr_v;
			}
		}
	}

	int mst_weight()
	{
		int weight = 0;
		for (int i = 0; i < G.nV; ++i)
			weight += distance[i];
		return weight;
	}
};

int main()
{
	Graph G(5);

	G.addEdge(0, 1, 3);
	G.addEdge(0, 2, 4);
	G.addEdge(3, 1, 6);
	G.addEdge(4, 1, 2);
	G.addEdge(1, 2, 5);
	G.addEdge(1, 4, 7);

	Prim P(G, 0);
	P.prim();
	cout << "MST WEIGHT : " << P.mst_weight() << endl;
	return 0;
}
