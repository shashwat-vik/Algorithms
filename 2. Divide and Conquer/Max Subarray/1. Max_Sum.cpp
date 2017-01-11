#include<iostream>
#include<vector>
#include<limits>
using namespace std;

typedef vector<int> veci;

int find_max_crossing_subarray(veci &arr, int low, int mid, int high)
{
	int left_sum = numeric_limits<int>::min(), max_left;
	for (int idx = mid, sum = 0; idx >= low; --idx)
	{
		sum += arr[idx];
		if (sum > left_sum)
			left_sum = sum, max_left = idx;
	}

	int right_sum = numeric_limits<int>::min(), max_right;
	for (int idx = mid + 1, sum = 0; idx <= high; ++idx)
	{
		sum += arr[idx];
		if (sum > right_sum)
			right_sum = sum, max_right = idx;
	}
	return (left_sum + right_sum);
}

int find_max_subarray(veci &arr, int low, int high)
{
	if (low == high)
		return arr[low];

	int mid = (low + high) / 2;

	int left_sum = find_max_subarray(arr, low, mid);
	int right_sum = find_max_subarray(arr, mid + 1, high);

	int cross_sum = find_max_crossing_subarray(arr, low, mid, high);

	if ((left_sum > right_sum) && (left_sum > cross_sum))
		return left_sum;
	if ((right_sum > left_sum) && (right_sum > cross_sum))
		return right_sum;
	else
		return cross_sum;
}

int main()
{
	veci day = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	veci price = { 100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94, 90, 97 };

	veci change = { 13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 };

	int low = 0;
	int high = change.size() - 1;

	cout << "MAX-SUM   : " << find_max_subarray(change, low, high) << endl;
}
