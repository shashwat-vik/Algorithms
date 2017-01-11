#include<iostream>
using namespace std;

int max(int a, int b) { return (a > b) ? a : b; }

int** knapsack(int *wt, int *val, int N, int W)
{
	int **dp = new int*[N + 1];
	for (int i = 0; i <= N; ++i)
		dp[i] = new int[W + 1]();

	for (int n = 0; n <= N; ++n) {
		for (int w = 0; w <= W; ++w) {
			if (n == 0 || w == 0)
				dp[n][w] = 0;
			else if (wt[n - 1] > w)
				dp[n][w] = dp[n - 1][w];
			else
				dp[n][w] = max(val[n - 1] + dp[n - 1][w - wt[n - 1]], dp[n - 1][w]);
		}
	}
	return dp;
}

int main()
{
	int wt[] = { 1,2,4 };
	int val[] = { 10,20,30 };

	int N = sizeof(val) / sizeof(val[0]);
	int W = 50;

	int **dp = knapsack(wt, val, N, W);
	cout << dp[N][W] << endl;

	for (int i = 0; i <= N; ++i)
		delete[] dp[i];
	delete[] dp;

	return 0;
}
