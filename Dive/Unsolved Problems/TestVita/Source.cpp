#include<iostream>
#include<list>
#include<string>

using namespace std;


class Index
{
private:
	list<int> in;
	list<int> out;
	friend class Graph;
};

class Graph
{
private:
	size_t nV;
	size_t* task_hours;
	Index* adj;
public:
	Graph(int nV)
	{
		this->nV = nV;
		adj = new Index[this->nV];
		this->task_hours = new size_t[this->nV]();
	}
	void addEdge(int x, int weight, int* dependency, int n_dependency)
	{
		task_hours[x] = weight;
		for (int i = 0; i <= n_dependency; ++i)
		{
			adj[dependency[i]].out.push_back(x);
			adj[x].in.push_back(dependency[i]);
		}
	}
	void print_hours()
	{
		for (size_t i = 0; i < this->nV; ++i)
			cout << "TASK: " << i << "\t" << task_hours[i] << endl;
	}
	void print_Graph()
	{
		for (size_t i = 0; i < this->nV; ++i)
		{
			cout << "NODE: " << i << endl;
			Index x = adj[i];
			list<int>::iterator p;
			cout << "\tIN :";
			for (p = x.in.begin(); p != x.in.end(); ++p)
				cout << *p << " ";
			cout << endl;
			cout << "\tOUT :";
			for (p = x.out.begin(); p != x.out.end(); ++p)
				cout << *p << " ";
			cout << endl << endl;;
		}
	}
	void printList(list<int> &x)
	{
		for (list<int>::iterator p = x.begin(); p != x.end(); ++p)
			cout << *p << " ";
		cout << endl;
	}

	void BFS(int s)
	{
		bool* visited = new bool[this->nV]();
		bool* executed = new bool[this->nV]();
		list<int>::iterator p;
		list<int>::iterator q;

		list<int> Queue;
		list<int> next_depth;

		visited[s] = true;
		executed[s] = true;
		Queue.push_back(s);

		size_t longest_job = 0, timer = task_hours[s];

		while (!Queue.empty())
		{
			s = Queue.front();
			Queue.pop_front();

			p = adj[s].out.begin();
			for (; p != adj[s].out.end(); ++p)
			{
				if (!visited[*p])
				{
					q = adj[*p].in.begin();
					bool green_signal = true;
					for (; q != adj[*p].in.end(); ++q)
					{
						if (!executed[*q])
							green_signal = false;
					}
					if (green_signal)
					{
						next_depth.push_back(*p);
						visited[*p] = true;
					}
				}
			}
			if (Queue.empty())
			{
				q = next_depth.begin();
				for (; q != next_depth.end(); ++q)
				{
					executed[*q] = true;
					if (task_hours[*q] > longest_job)
						longest_job = task_hours[*q];
				}
				//cout << "TIME TAKEN: " << longest_job << endl;
				timer += longest_job;
				Queue.swap(next_depth);
				//this->printList(Queue);
				longest_job = 0;
			}
		}
		cout << timer << endl;
	}
};

int main()
{
	int* dependency = new int[1010]();
	int T;
	cin >> T;

	while (T--)
	{
		int N, x, weight, n_dependency;
		int start_edge;
		cin >> N;
		Graph G(N+1);
		while (N--)
		{
			n_dependency = -1;
			for (int i = 1; i <= 3; i++)
			{
				if (i == 1)
					cin >> x;
				else if (i == 2)
					cin >> weight;
				else
				{
					string str;
					getline(cin, str);
					if (str == "")
					{
						start_edge = x;
					}
					else
					{
						string num = "";

						for (size_t j = 1; j < str.size(); ++j)
						{
							if (str[j] != ' ')
								num += str[j];
							if (str[j] == ' ' || (j == str.size() - 1))
							{
								int number = 0;
								if (num.size() == 2)
								{
									number = (num[0] - '0') * 10 + (num[1] - '0');
								}
								else
									number = (num[0] - '0');
								n_dependency++;
								//cout << "INDEX:" << n_dependency << " NUMBER:" << number << endl;
								dependency[n_dependency] = number;

								num = "";
							}
						}
					}
				}
			}

			//cout << "x: " << x << endl;
			//cout << "weight: " << weight << endl;
			//cout << "n_dependency: " << n_dependency << endl;
			//for (int i = 0; i <= n_dependency; ++i)
				//cout << "\t" << dependency[i] << endl;
			G.addEdge(x, weight, dependency, n_dependency);
		}
		//cout << "START: " << start_edge << endl;
		//G.print_Graph();
		//G.print_hours();

		G.BFS(start_edge);
	}
}