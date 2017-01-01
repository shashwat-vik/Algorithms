#include<iostream>
#include<list>
using namespace std;

class Graph
{
private:
	size_t nV;
	list<int>* adj;
	friend class DFS;
public:
	Graph(size_t nV)
	{
		this->nV = nV;
		adj = new list<int>[this->nV];
	}
	~Graph() { delete[] adj; }
	void addEdge(int x, int y)
	{
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
};

class DFS
{
private:
	const Graph &G;
	bool* explored;
	size_t* in_time;
	size_t* out_time;
	size_t timer;
public:
	DFS(Graph &g) : G(g)
	{
		this->explored = new bool[this->G.nV]();
		this->in_time = new size_t[this->G.nV]();
		this->out_time = new size_t[this->G.nV]();
		this->timer = 0;
	}
	~DFS()
	{
		delete[] explored;
		delete[] in_time;
		delete[] out_time;
	}
	void print_time()
	{
		cout << endl << endl;
		for (int i = 0; i < this->G.nV; ++i)
			cout << i << " --> IN: " << this->in_time[i] << "\tOUT: " << this->out_time[i] << endl;
		cout << endl;
	}
	bool query(int x, int y)
	{
		bool down_path = (this->in_time[x] < this->in_time[y]) && (this->out_time[x] > this->out_time[y]);
		bool up_path = (this->in_time[x] > this->in_time[y]) && (this->out_time[x] < this->out_time[y]);
		return (down_path || up_path);
	}

	void dfs(int vertex)
	{
		if (!this->explored[vertex])
		{
			this->timer++;
			this->explored[vertex] = true;
			this->in_time[vertex] = this->timer;

			list<int>::iterator p = this->G.adj[vertex].begin();
			for (; p != this->G.adj[vertex].end(); ++p)
			{
				if (!this->explored[*p])
				{
					cout << " --> " << *p;
					this->dfs(*p);
				}
			}
			this->timer++;
			this->out_time[vertex] = this->timer;
		}
	}
};

int main()
{
	Graph G(10);
	G.addEdge(1, 2);
	G.addEdge(1, 3);
	G.addEdge(3, 6);
	G.addEdge(2, 4);
	G.addEdge(2, 5);
	G.addEdge(5, 7);
	G.addEdge(5, 8);
	G.addEdge(5, 9);

	DFS D(G);
	int start = 1;
	cout << "PATH --> " << start;
	D.dfs(start);
	D.print_time();

	int u, v;
	while (true)
	{
		cin >> u >> v;
		if (D.query(u, v))
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;
	}
}
