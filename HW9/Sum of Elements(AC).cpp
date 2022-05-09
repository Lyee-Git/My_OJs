#include<iostream>
#include<unordered_map>
#include<algorithm>
#include<vector>
//#define OJ
using namespace std;
vector<vector<int>> edge;
int n, a, b;
void DFS(int u, int fa, int *Train, int *coins, int *vis)
{
    vis[u] = 1;
    if (edge[u].size() == 1)
    {
        if (Train[edge[u][0]] == -1)
        {
            if (coins[u] + coins[edge[u][0]] == a)
                Train[u] = Train[edge[u][0]] = 0;
            else
                Train[u] = Train[edge[u][0]] = 1;
        }
        return;
    }
    for (auto v : edge[u])
    {
        if (v == fa || v == u) continue;
        if (!vis[v])
            DFS(v, u, Train, coins, vis);
    }
    if (Train[u] == -1)
    {
        for (auto v : edge[u])
            if (Train[v] == -1)
            { 
                if (coins[u] + coins[v] == a)
                    Train[u] = Train[v] = 0; 
                else
                    Train[u] = Train[v] = 1;
                break;
            }
    }
}

int main()
{
    cin >> n >> a >> b;
    int *coins = new int[n], *Train = new int[n], *vis = new int[n]; 
    edge.resize(n);
    unordered_map<int, int> index;
    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
        index[coins[i]] = i;
        Train[i] = -1; vis[i] = 0;
    }
    for (int i = 0; i < n;i++)
    {
        if (index.count(a - coins[i]) )//&& a != 2 * coins[i])
            edge[i].emplace_back(index[a - coins[i]]);
        if (index.count(b - coins[i]))// && b != 2 * coins[i])
            edge[i].emplace_back(index[b - coins[i]]);
    }
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
            DFS(i, -1, Train, coins, vis);
    }
    bool success = true;
    for (int i = 0; i < n; i++) {
        if (Train[i] == -1)
            {
                // if (a == 2 * coins[i])
                //     Train[i] = 0;
                // if (b == 2 * coins[i])
                //     Train[i] = 1;
                // if (Train[i] == -1)
                // {
                success = false;
                break;
                // }
            }
    }
    if (!success) 
        cout << "0" << endl;
    else {
        cout << "1" << endl;
        for (int i = 0; i < n - 1; i++) cout << Train[i] << " ";
        cout << Train[n - 1];
    }
delete coins; delete Train; delete vis;
#ifndef OJ
    system("pause");
#endif
    return 0; 
}