#include<iostream>
#include<vector>
#include<string>
#define veci vector<int>
using namespace std;

void print_vector(veci x)
{
	for (size_t i = 0; i < x.size(); ++i)
		cout << x[i] << " ";
	cout << endl;
}
void merge_sort(veci data, string dir)
{
	cout << dir << " --> ";
	print_vector(data);
	if (data.size() == 1)
	{
		cout << "EXIT " << dir << " : " << data[0] << endl << endl;
		return;
	}
	size_t middle = data.size() / 2;

	merge_sort(veci(data.begin(), data.begin() + middle), "LEFT");
	merge_sort(veci(data.begin() + middle, data.end()), "RIHT");

	cout << "EXIT THREAD\n" << endl;
}

int main()
{
	vector<int> data;
	data.push_back(4);
	data.push_back(1);
	data.push_back(3);
	data.push_back(9);
	data.push_back(7);
	data.push_back(2);

	merge_sort(data, "");
}
