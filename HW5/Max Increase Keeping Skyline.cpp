// Leetcode 807
#include<iostream>
#include<limits.h>
using namespace std;
//#define OJ

int main()
{
    int N;
    cin >> N;
    int city[N][N], max_rows[N], max_cols[N], max_increment = 0;
    for (int i = 0; i < N; i++)
        max_rows[i] = max_cols[i] = INT_MIN;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            cin >> city[i][j];
            if (city[i][j] > max_rows[i])
                max_rows[i] = city[i][j];
            if (city[i][j] > max_cols[j])
                max_cols[j] = city[i][j];
        }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            int limit = max_rows[i] < max_cols[j] ? max_rows[i] : max_cols[j];
            if (limit > city[i][j])
                max_increment += limit - city[i][j];
        }
    cout << max_increment << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}