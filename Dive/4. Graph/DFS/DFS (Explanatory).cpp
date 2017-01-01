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
	void addEdge(int x, int y) { adj[x].push_back(y); adj[y].push_back(x); }
	void printList(list<int> &x)
	{
		for (list<int>::iterator p = x.begin(); p != x.end(); ++p)
			cout << *p << " ";
		cout << endl;
	}
	void printStack(list<int> &x)
	{
		cout << "STACK: ";
		for (list<int>::iterator p = x.begin(); p != x.end(); ++p)
			cout << *p << " ";
		cout << endl << endl;
	}

	void DFS(int s)
	{
		bool* explored = new bool[this->nV]();
		int* parent = new int[this->nV];
		list<int> Stack;
		list<int>::iterator p;

		parent[s] = -1;
		Stack.push_front(s);

		while (!Stack.empty())
		{
			s = Stack.front();
			Stack.pop_front();

			if (!explored[s])
			{
				explored[s] = true;
				cout << "EXPLORING: " << s << endl << "PUSHED: ";
				for (p = adj[s].begin(); p != adj[s].end(); ++p)
				{
					if (!explored[*p])
						parent[*p] = s;
					cout << *p << " ";
					Stack.push_front(*p);
				}
				cout << endl;
			}
			this->printStack(Stack);
		}
		for (int i = 0; i < this->nV; ++i)
			cout << "PARENT: " << i << " --> " << parent[i] << endl;
		cout << endl;

        delete[] explored;
        delete[] parent;
	}
};

int main()
{
	Graph G(6);
	G.addEdge(0, 1);
	G.addEdge(0, 3);
	G.addEdge(1, 2);
	G.addEdge(1, 4);
	G.addEdge(3, 4);
	G.addEdge(3, 5);

	G.DFS(0);
}
