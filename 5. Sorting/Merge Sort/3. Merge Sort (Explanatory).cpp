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

veci merge_sort(veci data)
{
	if (data.size() == 1)
		return data;

	size_t middle = data.size() / 2;

	// LEFT  : [begin, middle)
	// RIGHT : [middle, end)
	// THIS WORKS BECAUSE VECTOR ITERATORS ARE USED
	// AND 'end' ITERATOR CORRESPONDS TO
	// ONE ELEMENT AHEAD OF LAST IN THE VECTOR
	// THUS ALL ELEMENTS ARE HANDLED
	veci left = merge_sort(veci(data.begin(), data.begin() + middle));
	veci right = merge_sort(veci(data.begin() + middle, data.end()));

	veci result(data.size(), 0);

	cout << "DATA : ";
	print_vector(data);
	cout << "LEFT : ";
	print_vector(left);
	cout << "RIGHT : ";
	print_vector(right);
	size_t dPtr = 0, lPtr = 0, rPtr = 0;
	while (dPtr < data.size())
	{
		if (lPtr == left.size())
			result[dPtr] = right[rPtr], rPtr++;

		else if (rPtr == right.size())
			result[dPtr] = left[lPtr], lPtr++;

		else if (left[lPtr] < right[rPtr])
			result[dPtr] = left[lPtr], lPtr++;

		else
			result[dPtr] = right[rPtr], rPtr++;

		dPtr++;
	}
	cout << "RESULT : ";
	print_vector(result);
	cout << endl;
	return result;
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

	veci result = merge_sort(data);
	return 0;
}
