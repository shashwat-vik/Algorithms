#include<iostream>
using namespace std;

int max(int a, int b) { return (a > b) ? a : b; }

int knapsack(int *wt, int *val, int W, int N)
{
	if (N == 0 || W == 0)
		return 0;

	if (wt[N - 1] > W)
		return knapsack(wt, val, W, N - 1);
	else
		return max(val[N - 1] + knapsack(wt, val, W - wt[N - 1], N - 1), knapsack(wt, val, W, N-1));
}

int main()
{
	int wt[] = { 60, 100, 120 };
	int val[] = { 10, 20, 30 };
	int N = sizeof(wt) / sizeof(wt[0]);
	int W = 130;

	cout << knapsack(wt, val, W, N);

    return 0;
}
