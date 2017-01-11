#include<iostream>
#include<vector>
#define veci vector<int>
using namespace std;

void print_vector(veci x)
{
	for (size_t i = 0; i < x.size(); ++i)
		cout << x[i] << " ";
	cout << endl;
}

void insertion_sort(veci& data)
{
	int i, j, key;

	// START FROM SECOND ELEMENT
	// BECAUSE ONE ELEMENT IS ALWAYS SORTED
	for (i = 1; i < int(data.size()); ++i)
	{
		key = data[i];
		// THEN CHECK WHERE IT CAN FIT BEFORE
		// THAT IS IN RANGE [0,i-1]
		j = i - 1;
		// THE LOOP OPERATES ONLY IF data[i-1] > data[i] because [0, i-1] is already SORTED
		// THUS FOR ALREADY SORTED ARRAY, THIS PART NEVER RUNS
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
	//{5, 2, 4, -6, 1, 3}

	veci data;
	data.push_back(5);
	data.push_back(2);
	data.push_back(4);
	data.push_back(-6);
	data.push_back(1);
	data.push_back(3);

	insertion_sort(data);
	cout << "RESULT : ";
	print_vector(data);
}
