#include<iostream>
#include<vector>
#include<tuple>
#include<limits>
using namespace std;

typedef vector<int> veci;
typedef tuple<int, int, int> sub_data;
// (LOW, HIGH, SUM)

sub_data find_max_crossing_subarray(veci& arr, int low, int mid, int high)
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

	return sub_data(max_left, max_right, left_sum + right_sum);
}

sub_data find_max_subarray(veci& arr, int low, int high)
{
	if (low == high)
		return sub_data(low, high, arr[low]);

	int mid = (low + high) / 2;

	sub_data left = find_max_subarray(arr, low, mid);
	sub_data right = find_max_subarray(arr, mid + 1, high);

	sub_data cross = find_max_crossing_subarray(arr, low, mid, high);

	if ((get<2>(left) > get<2>(right)) && (get<2>(left) > get<2>(cross)))
		return left;
	else if ((get<2>(right) > get<2>(left)) && (get<2>(right) > get<2>(cross)))
		return right;
	else
		return cross;
}

int main()
{
	veci day = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	veci price = { 100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94, 90, 97 };

	veci change = { 13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 };

	int low = 0;
	int high = change.size()-1;

	sub_data result = find_max_subarray(change, low, high);
	cout << "MAX-LEFT IDX  : " << get<0>(result) << endl;
	cout << "MAX-RIGHT IDX : " << get<1>(result) << endl;
	cout << "MAX-SUM   : " << get<2>(result) << endl;
}
