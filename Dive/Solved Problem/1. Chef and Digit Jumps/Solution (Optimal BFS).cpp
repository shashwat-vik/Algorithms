#include<iostream>
#include<cstring>
#include<queue>
#include<string>

using namespace std;

int main()
{
	vector<int> V[10];
	queue<int> Q;
	bool visited[100004];
	int d[100004];
	int val, idx, nidx;
	memset(visited, false, sizeof(visited));

	string s;
	cin >> s;

	for (int i = 1; i < s.size(); ++i)
	{
		val = s[i] - '0';
		V[val].push_back(i);
	}

	d[0] = 0;
	visited[0] = true;
	Q.push(0);

	while (!Q.empty())
	{
		idx = Q.front();
		Q.pop();
		if (idx == (s.size() - 1))
			break;
		val = s[idx] - '0';
		for (int i = 0; i < V[val].size(); ++i)
		{
			nidx = V[val][i];
			if (!visited[nidx])
			{
				d[nidx] = 1 + d[idx];
				visited[nidx] = true;
				Q.push(nidx);
			}
		}
		V[val].clear();
		
		if ((idx - 1) >= 0 && !visited[idx - 1])
		{
			d[idx - 1] = 1 + d[idx];
			visited[idx - 1] = true;
			Q.push(idx - 1);
		}
		if ((idx + 1) < s.size() && !visited[idx + 1])
		{
			d[idx + 1] = 1 + d[idx];
			visited[idx + 1] = true;
			Q.push(idx + 1);
		}
	}
	cout << d[s.size() - 1] << endl;
	return 0;
}