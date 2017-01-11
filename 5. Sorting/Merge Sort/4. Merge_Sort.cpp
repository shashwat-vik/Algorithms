#include<iostream>
#include<vector>
#define veci vector<int>
using namespace std;

veci merge_sort(veci data)
{
	if (data.size() == 1)
		return data;

	size_t middle = data.size() / 2;

	veci left = merge_sort(veci(data.begin(), data.begin() + middle));
	veci right = merge_sort(veci(data.begin() + middle, data.end()));

	veci result(data.size(), 0);

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
