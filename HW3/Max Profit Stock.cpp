#include<iostream>
#include<vector>
#include<limits.h>
//#define OJ
using namespace std;

int main()
{
    vector<int> prices;
    int price;
    while (cin >> price)
        prices.emplace_back(price);
    int n = prices.size();
    /* 6 States: 
        [n][i][j]
        i indicates num of sales: 0, 1, 2
        j indicates state of holing a stock or not: 0, 1
    */
    int DP[n][3][2], maxProfit = 0;
    DP[0][0][0] = 0;
    DP[0][0][1] = -prices[0];
    DP[0][1][0] = DP[0][1][1] = DP[0][2][0] = DP[0][2][1] = INT_MIN / 2;
    for (int i = 1; i < n; i++)
    {
        DP[i][0][0] = DP[i - 1][0][0];
        DP[i][0][1] = max(DP[i - 1][0][0] - prices[i], DP[i - 1][0][1]);
        DP[i][1][0] = max(DP[i - 1][1][0], DP[i][0][1] + prices[i]);
        DP[i][1][1] = max(DP[i - 1][1][1], DP[i - 1][1][0] - prices[i]);
        DP[i][2][0] = max(DP[i - 1][2][0], DP[i - 1][1][1] + prices[i]);
        DP[i][2][1] = max(DP[i - 1][2][1], DP[i - 1][2][0] - prices[i]);
    }
    maxProfit = max(DP[n - 1][1][0], DP[n - 1][2][0]);
    cout << max(maxProfit, 0) << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}