#include<iostream>
#include<string>
using namespace std;

void split(int* arr, int L, int H)
{
	if (L == H)
	{
		cout << "EXIT (L,H) : " << L << ", " << H << endl;
		return;
	}
	int M = (L + H) / 2;
	cout << "LEFT ENT -- CURRENT L,H : " << L << ", " << M << endl;
	split(arr, L, M);
	cout << "RIHT ENT -- CURRENT L,H : " << M+1 << ", " << H << endl;
	split(arr, M + 1, H);
	cout << "THRD EXT" << endl;
}

int main()
{
	int arr[] = { 4,1,3,9,7,2 };
	int n = 6;

	split(arr, 0, n - 1);

	return 0;
}
