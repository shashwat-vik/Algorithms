#include<iostream>
#include<limits>
using namespace std;

void print_array(int *arr, int n)
{
	for (int i = 0; i < n; ++i)
		cout << arr[i] << '\t';
	cout << endl;
}

void merge(int *arr, int p, int q, int r)
{
	int n1 = q - p + 1, n2 = r - q;
	int *L = new int[n1 + 1];		// Extra index for Sentinel Card
	int *R = new int[n2 + 1];

	for (int i = p; i <= q; ++i)
		L[i - p] = arr[i];
	L[n1] = numeric_limits<int>::max();		// Sentinel Card on (n1+1)'th element
	for (int i = q + 1; i <= r; ++i)
		R[i - (q + 1)] = arr[i];
	R[n2] = numeric_limits<int>::max();

	int lPtr = 0, rPtr = 0;
	for (int i = p; i <= r; ++i) {
		if (L[lPtr] < R[rPtr])
			arr[i] = L[lPtr], lPtr++;
		else
			arr[i] = R[rPtr], rPtr++;
	}
	delete[] L, delete[] R;
}

void merge_sort(int *arr, int p, int r)
{
	if (p < r) {
		int q = (p + r) / 2;
		merge_sort(arr, p, q);
		merge_sort(arr, q + 1, r);
		merge(arr, p, q, r);
	}
}

int main()
{
	int arr[] = { 11,-9,3,6,0,2 }, n = 6;

	merge_sort(arr, 0, n - 1);
	print_array(arr, n);

	return 0;
}
