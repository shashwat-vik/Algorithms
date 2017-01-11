#include<iostream>
#include<vector>
using namespace std;

#define veci vector<int>

void display_vector(veci& x)
{
	for (size_t i = 0; i < x.size(); ++i)
		cout << x[i] << '\t';
	cout << endl;
}

void merge_sort(veci& arr, size_t L, size_t R)
{
	if (L == R)
	{
		cout << "RET : " << L << ',' << R << endl;
		return;
	}
	size_t M = (L+R) / 2;

	merge_sort(arr, L, M);			// LEFT
	merge_sort(arr, M+1, R);		// RIGHT

	veci result(R-L+1, 0);
	size_t lPtr = L, rPtr = M+1, dPtr = 0;
	while (dPtr < result.size())
	{
		if (lPtr == (M+1))
			result[dPtr] = arr[rPtr], rPtr++;
		else if (rPtr == (R+1))
			result[dPtr] = arr[lPtr], lPtr++;
		else if (arr[lPtr] < arr[rPtr])
			result[dPtr] = arr[lPtr], lPtr++;
		else
			result[dPtr] = arr[rPtr], rPtr++;
		dPtr++;
	}
	for (int i = L; i <= R; ++i)
		arr[i] = result[i - L];

	cout << "(L,R) - (" << L << ',' << R << ')' << endl;
	cout << "RESULT : "; display_vector(result);
	cout << "BRANCH EXIT" << endl << endl;

	return;
}

int main()
{
	veci arr = { 4,1,3,9,7,2 };
	merge_sort(arr, 0, arr.size()-1);
	return 0;
}
