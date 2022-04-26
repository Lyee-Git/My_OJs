#include<vector>
#include<iostream>
#include<limits.h>
//#define OJ
using namespace std;

vector<int> edge[50000];

void DFS(int x, int *dis, int x0)
{
    for(auto it:edge[x])
    {
        if (it == x0)
            continue;
        dis[it] = dis[x] + 1;
        DFS(it, dis, x);
    }
}

int main()
{
    int n, x, y, res = 0;
    cin >> n >> x >> y;
    int disA[50000] = {0}, disB[50000] = {0};
    if (n == 1)
    {
        cout << "0" << endl;
        return 0;
    }
    for (int i = 0; i < n - 1; i++)
    {
        int tmpA, tmpB;
        cin >> tmpA >> tmpB;
        edge[tmpA].emplace_back(tmpB);
        edge[tmpB].emplace_back(tmpA);
    }
    DFS(x, disA, 0);
    DFS(y, disB, 0);
    for (int i = 1; i <= n; i++)
    {
        if (edge[i].size() == 1 && disA[i] > disB[i])
            res = max(res, disA[i]);
    }
    cout << res << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;  
}