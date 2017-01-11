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
	void addEdge(int x, int y)
	{
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	void printList(list<int> &x)
	{
		for (list<int>::iterator p = x.begin(); p != x.end(); ++p)
			cout << *p << " ";
		cout << endl;
	}

	void BFS(int s)
	{
		bool* discovered = new bool[this->nV]();
		list<int> next_depth;
		list<int> Queue;
		list<int>::iterator p;
		size_t level = 0;

		Queue.push_back(s);
		discovered[s] = true;

		cout << endl << "LEVEL: " << level << endl;
		this->printList(Queue);

		while (!Queue.empty())
		{
			s = Queue.front();
			Queue.pop_front();

			for (p = adj[s].begin(); p != adj[s].end(); ++p)
			{
				if (!discovered[*p])
				{
					next_depth.push_back(*p);
					discovered[*p] = true;
				}
			}
			if (Queue.empty())
			{
				level++;
				Queue.swap(next_depth);
				cout << endl << "LEVEL: " << level << endl;
				this->printList(Queue);
			}
		}
		delete[] discovered;
	}
};

int main()
{
	Graph G(7);

	G.addEdge(0, 1);
	G.addEdge(1, 2);
	G.addEdge(2, 6);
	G.addEdge(2, 3);
	G.addEdge(3, 6);
	G.addEdge(1, 3);
	G.addEdge(1, 4);
	G.addEdge(4, 3);
	G.addEdge(0, 4);
	G.addEdge(4, 5);
	G.addEdge(5, 3);
	G.addEdge(5, 6);

	G.BFS(1);
}
