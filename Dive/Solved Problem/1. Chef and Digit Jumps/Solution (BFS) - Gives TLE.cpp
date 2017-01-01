#include<iostream>
#include<list>
#include<map>
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
	~Graph() { delete[] adj; }
 
	void addEdge(int x, int y)
	{
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	void addEdge(int x, list<int>& nodes)
	{
		for (list<int>::iterator p = nodes.begin(); p != nodes.end(); ++p)
			addEdge(x, *p);
	}
	int BFS(int s, int end)
	{
		list<int> queue;
		list<int> to_visit;
		list<int>::iterator p;
		int level = 0;
		bool* visited = new bool[V];
		for (int i = 0; i < V; ++i)
			visited[i] = false;
 
		visited[s] = true;
		queue.push_back(s);
 
		level++;
 
		while (!queue.empty())
		{
			s = queue.front();
			queue.pop_front();
			if (s == end)
				break;
			for (p = adj[s].begin(); p != adj[s].end(); ++p)
			{
				if (!visited[*p])
				{
					to_visit.push_back(*p);
					visited[*p] = true;
				}
			}
			if (queue.empty())
			{
				queue.swap(to_visit);
				if (queue.empty())
					break;
				level++;
			}
		}
		return level - 1;
	}
};
 
int main()
{
	typedef map<char,list<int> > mapping;
 
	mapping node_state;
	pair<mapping::iterator, bool> status;
	int start, end;
 
	string s;
	cin >> s;
 
	start = 0;
	end = s.size() - 1;
 
	Graph G(s.size());
 
	status = node_state.insert(make_pair(s[0],list<int>(1,0)));
 
	for (size_t i = 1; i < s.size(); ++i)
	{
 
		status = node_state.insert(make_pair(s[i],list<int>(1,i)));
		if (status.second == false)
		{
			if (status.first->second.back() != (i - 1))
				G.addEdge(i - 1, i);
			G.addEdge(i, status.first->second);
			status.first->second.push_back(i);
		}
		else
			G.addEdge(i - 1, i);
	}
 
	cout << G.BFS(start, end) << endl;
 
	return 0;
}