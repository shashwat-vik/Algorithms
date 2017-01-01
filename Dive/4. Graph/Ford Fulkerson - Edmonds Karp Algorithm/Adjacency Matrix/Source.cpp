#include<iostream>
#include<list>
#include<limits>
#include<algorithm>
using namespace std;

class Graph
{
private:
	int nV;
	int** matrix;
	friend class MaxFlow;
public:
	Graph(int nV)
	{
		this->nV = nV;
		matrix = new int*[this->nV];
		for (int i = 0; i < this->nV; ++i)
			matrix[i] = new int[this->nV]();
	}
	~Graph()
	{
		for (int i = 0; i < this->nV; ++i)
			delete[] matrix[i];
	}

	void readGraph()
	{
		int capacity;
		for (int u = 0; u < this->nV; ++u)
		{
			for (int v = 0; v < this->nV; ++v)
			{
				cin >> capacity;
				this->matrix[u][v] = capacity;
			}
		}
	}
};

class MaxFlow
{
private:
	const Graph& G;
	int** rGraph;
	int src;
	int sink;
	int* parent;
public:
	MaxFlow(const Graph& _G, int s, int t) : G(_G)
	{
		rGraph = new int*[G.nV];
		this->src = s;
		this->sink = t;
		parent = new int[G.nV]();
		parent[this->src] = -1;

		for (int u = 0; u < G.nV; ++u)
		{
			rGraph[u] = new int[G.nV];
			for (int v = 0; v < G.nV; ++v)
				rGraph[u][v] = G.matrix[u][v];
		}
	}
	~MaxFlow()
	{
		for (int i = 0; i < G.nV; ++i)
			delete[] rGraph[i];
		delete[] parent;
	}

	bool BFS()
	{
		bool* visited = new bool[G.nV]();
		list<int> Queue;

		visited[this->src] = true;
		Queue.push_back(this->src);

		while (!Queue.empty())
		{
			int u = Queue.front();
			Queue.pop_front();

			for (int v = 0; v < G.nV; ++v)
			{
				if (!visited[v] && this->rGraph[u][v] > 0)
				{
					visited[v] = true;
					parent[v] = u;
					Queue.push_back(v);
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
				path_flow = min(path_flow, rGraph[u][v]);
			}
			for (v = this->sink; v != this->src; v = parent[v])
			{
				u = parent[v];
				rGraph[u][v] -= path_flow;
				rGraph[v][u] += path_flow;
			}
			max_flow += path_flow;
		}

		return max_flow;
	}
};

int main()
{
	Graph G(6);
	G.readGraph();

	MaxFlow M(G, 0, 5);

	cout << "MAX FLOW: " << M.fordFulkerson() << endl;

	return 0;
}

/*INPUT
0 16 13 0 0 0
0 0 10 12 0 0
0 4 0 0 14 0
0 0 9 0 0 20
0 0 0 7 0 4
0 0 0 0 0 0
*/
