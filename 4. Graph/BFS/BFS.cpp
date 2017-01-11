#include<iostream>
#include<list>
using namespace std;

class Graph
{
private:
	int nV;
	list<int>* adj;
public:
	Graph(int nV)
	{
		this->nV = nV;
		this->adj = new list<int>[this->nV];
	}
	~Graph() { delete[] adj; }
	void addEdge(int x, int y) { adj[x].push_back(y); }

	void BFS(int s)
	{
		bool* visited = new bool[this->nV]();
		list<int> Queue;
		list<int>::iterator p;

		visited[s] = true;
		Queue.push_back(s);

		while (!Queue.empty())
		{
			s = Queue.front();
			Queue.pop_front();
			cout << s << " ";
			for (p = adj[s].begin(); p != adj[s].end(); ++p)
			{
				if (!visited[*p])
				{
					visited[*p] = true;
					Queue.push_back(*p);
				}
			}
		}
		cout << endl;
		delete[] visited;
	}
};

int main()
{
	Graph G(4);

	G.addEdge(0, 1);
	G.addEdge(0, 2);
	G.addEdge(1, 2);
	G.addEdge(2, 0);
	G.addEdge(2, 3);
	G.addEdge(3, 3);

	cout << "Following is Breadth First Traversal (starting from vertex 2) \n";
	G.BFS(2);
}
