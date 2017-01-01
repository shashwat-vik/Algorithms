#include<iostream>
#include<map>
#include<list>
#include<string>

using namespace std;

class Graph
{
private:
	int V;
	list<int>* adj;
public:
	Graph(int v)
	{
		V = v;
		adj = new list<int>[V];
	}
	void addEdge(int x, int y)
	{
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	void print()
	{
		list<int>::iterator p;
		for (int i = 0; i < V; ++i)
		{
			cout << i << " : ";
			for (p = adj[i].begin(); p != adj[i].end(); ++p)
				cout << *p << " ";
			cout << endl;
		}
	}
};

int main()
{
	typedef map<char, int> mapping;

	mapping node_state;
	pair<mapping::iterator, bool> status;

	string s = "56781757";

	Graph G(8);

	status = node_state.insert(make_pair(s[0], 0));

	for (int i = 1; i < s.size(); ++i)
	{
		
		status = node_state.insert(make_pair(s[i], i));
		// UPDATES THE VALUE OF CURRENT INDEX FOR THE DUPLICATE KEY/NODE
		// TO THE NEWLY ALLOTED ONE
		// AND ADD TWO BIDERCTIONAL EDGES
		// ONE BETWEEN CURRENT INDEX AND NEW INDEX OF DUPLICATE KEY/NODE
		// SECOND BETWEEN THE NEW INDEX OF DUPLICATE NODE AND (i-1)'th NODE
		if (status.second == false)
		{
			G.addEdge(i-1, i);	// CONNECTING THE CURRENT CONFIG
			G.addEdge(status.first->second, i);	//CONNECTING THE PREVIOUS VER WITH CURR VER
			status.first->second = i;
		}
		// ADDING EDGE WITH NEW UNIQUE INDEX OF i'th KEY/NODE
		// AND (i-1)th KEY/NODE
		// IF IT DOESN'I EXISTS
		else
			G.addEdge(i - 1, i);
	}
	G.print();
	return 0;
}