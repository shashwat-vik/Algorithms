#include<iostream>
#include<vector>
#define veci vector<int>
using namespace std;

void insertion_sort(veci& data)
{
	int i, j, key;
	for (i = 1; i < int(data.size()); ++i)
	{
		key = data[i];
		j = i - 1;
		while (j >= 0 && (data[j] > key))
		{
			data[j + 1] = data[j];
			j--;
		}
		data[j + 1] = key;
	}
}

int main()
{
	veci data;
	data.push_back(5);
	data.push_back(2);
	data.push_back(4);
	data.push_back(-6);
	data.push_back(1);
	data.push_back(3);

	insertion_sort(data);
}
