#include<iostream>

using namespace std;

int execute_DP(int n)
{
    int dp[n+1];
    dp[1]=0;    //TRIVIAL CASE
    for(int i=2; i<=n; ++i)
    {
        dp[i] = 1+dp[i-1];
        if(i%2==0)
            dp[i] = min(dp[i],1+dp[i/2]);
        if(i%3==0)
            dp[i] = min(dp[i],1+dp[i/3]);
    }
    return dp[n];
}

int main()
{
    cout << execute_DP(10) << endl;
    return 0;
}
