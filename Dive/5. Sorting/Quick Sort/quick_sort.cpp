#include<iostream>
using namespace std;

void print_array(int* arr, int n)
{
	for (int i = 0; i < n; ++i)
		cout << arr[i] << '\t';
	cout << endl;
}

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

int partition(int* arr, int L, int R)
{
	int pivot = arr[R];
	int i = L - 1;         // [i,j) <= pivot
	for (int j = L; j < R; ++j) {
		if (arr[j] <= pivot) {
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[R]);
	return i + 1;
}

void quick_sort(int* arr, int L, int R)
{
	if (L < R) {
		int q = partition(arr, L, R);
		quick_sort(arr, L, q - 1);
		quick_sort(arr, q + 1, R);
	}
}

int main()
{
	int arr[] = { -1,9,8,2,3,1 };
	int n = 6;
	cout << "BEFORE : ";  print_array(arr, n);
	quick_sort(arr, 0, n-1);
	cout << "AFTER  : ";  print_array(arr, n);
	return 0;
}
