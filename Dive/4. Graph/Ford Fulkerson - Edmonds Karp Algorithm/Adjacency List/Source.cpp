#include<iostream>
#include<list>
#include<map>
#include<limits>
#include<algorithm>
using namespace std;

class Graph
{
private:
	int nV;
	map<int, int>* adj;
	friend class MaxFlow;
public:
	Graph(int nV)
	{
		this->nV = nV;
		adj = new map<int, int>[this->nV];
	}
	~Graph() { delete[] adj; }

	void addEdge(int u, int v, int cap) { adj[u].insert(make_pair(v, cap)); }
};

class MaxFlow
{
private:
	const Graph& G;
	Graph* rGraph;
	int src;
	int sink;
	int* parent;
public:
	MaxFlow(const Graph& _G, int s, int t) : G(_G)
	{
		rGraph = new Graph(G.nV);
		this->src = s;
		this->sink = t;
		parent = new int[G.nV];
		parent[this->src] = -1;

		int u;
		map<int, int>::iterator v;
		for (u = 0; u < G.nV; ++u)
		{
			for (v = G.adj[u].begin(); v != G.adj[u].end(); ++v)
			{
				rGraph->addEdge(u, v->first, v->second);
				if (G.adj[v->first].find(u) == G.adj[v->first].end())
					rGraph->addEdge(v->first, u, 0);
			}
		}
	}
	~MaxFlow() { delete[] parent; delete rGraph; }

	bool BFS()
	{
		bool* visited = new bool[rGraph->nV]();

		list<int> Queue;

		visited[this->src] = true;
		Queue.push_back(this->src);

		int u;
		map<int, int>::iterator v;
		while (!Queue.empty())
		{
			u = Queue.front();
			Queue.pop_front();

			for (v = rGraph->adj[u].begin(); v != rGraph->adj[u].end(); ++v)
			{
				if (!visited[v->first] && v->second > 0)
				{
					visited[v->first] = true;
					this->parent[v->first] = u;
					Queue.push_back(v->first);
				}
			}
		}
		bool status = visited[this->sink];
		delete[] visited;
		return status;
	}
	int fordFulkerson()
	{
		int max_flow = 0;
		int u, v, path_flow;

		while (this->BFS())
		{
			path_flow = numeric_limits<int>::max();
			for (v = this->sink; v != this->src; v = parent[v])
			{
				u = parent[v];
				path_flow = min(path_flow, rGraph->adj[u].find(v)->second);
			}
			for (v = this->sink; v != this->src; v = parent[v])
			{
				u = parent[v];
				rGraph->adj[u].find(v)->second -= path_flow;
				rGraph->adj[v].find(u)->second += path_flow;
			}
			max_flow += path_flow;
		}
		return max_flow;
	}
};


int main()
{
	Graph G(6);
	G.addEdge(0, 1, 16);
	G.addEdge(0, 2, 13);
	G.addEdge(1, 2, 10);
	G.addEdge(2, 1, 4);
	G.addEdge(1, 3, 12);
	G.addEdge(3, 2, 9);
	G.addEdge(2, 4, 14);
	G.addEdge(4, 3, 7);
	G.addEdge(3, 5, 20);
	G.addEdge(4, 5, 4);

	MaxFlow M(G, 0, 5);
	cout << "MAX FLOW: " << M.fordFulkerson() << endl;
	return 0;
}
