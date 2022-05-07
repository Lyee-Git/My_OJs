#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
#include<sstream>
#include<string>
//#define OJ
using namespace std;
enum Color {WHITE, GRAY, BLACK};

void DFS(int u, vector<vector<int>>& edge, stack<int>& s, Color *color)
{
    color[u] = GRAY;
    int n = edge[u].size();
    for (int i = 0;i < n;i ++)
        if (color[edge[u][i]] == WHITE)
            DFS(edge[u][i], edge, s, color);
    color[u] = BLACK;
    s.push(u); 
}

void DFS_SCC(int u, vector<vector<int>>& edge, Color *color, int *SCC, int SCCnum)
{
    color[u] = GRAY;
    if (SCC[u] == 0)
        SCC[u] = SCCnum;
    int n = edge[u].size();
    for (int i = 0;i < n;i ++)
        if (color[edge[u][i]] == WHITE)
            DFS_SCC(edge[u][i], edge, color, SCC, SCCnum);
    color[u] = BLACK;
}

void DFS_IMPACT(int u, vector<vector<int>>& edge, Color *color, int& impact)
{
    color[u] = GRAY;
    int n = edge[u].size();
    for (int i = 0;i < n;i ++)
        if (color[edge[u][i]] == WHITE)
            DFS_IMPACT(edge[u][i], edge, color, impact);
    color[u] = BLACK;
    impact++;
}

int main()
{
    vector<vector<int>> edge;
    string neighbor;
    while (getline(cin, neighbor))
    {
        stringstream sstream(neighbor);
        int tmp;
        vector<int> line;
        while (sstream >> tmp)
            line.push_back(tmp);
        edge.push_back(line);
    }
    int n = edge.size();
    Color *color = new Color[n];
    for (int i = 0; i < n; i++)
        color[i] = WHITE;
    stack<int> s;
    for (int i = 0; i < n; i++) // First DFS, push nodes to stack
    {
        if (color[i] == WHITE)
            DFS(i, edge, s,color);
    }
    vector<vector<int>> transpose(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0, m = edge[i].size(); j < m; j++)
            transpose[edge[i][j]].push_back(i);
    }
    int SCC[n] = {0}, SCCnum = 0;
    vector<int> contraction; // Contraction Graph: Representative nodes of each SCC
    for (int i = 0; i < n; i++)
    {
        color[i] = WHITE;
        SCC[i] = 0;
    }
    while (!s.empty())
    {
        int u = s.top();
        s.pop();
        if (color[u] == WHITE)
        {
            SCCnum++;
            DFS_SCC(u, transpose, color, SCC, SCCnum); // Conduct DFS on transposed Graph, Marking each SCC
            contraction.push_back(u);
        }
    }
    int n_contraction = contraction.size();
    int maxImpact = -1;
    vector<int> res; // Result: Nodes with maximum impacts
    for (int i = 0; i < n_contraction; i++)
    {
        for (int j = 0; j < n; j++)
            color[j] = WHITE;
        int impact = 0;
        DFS_IMPACT(contraction[i], edge, color, impact);
        if (impact > maxImpact)
        {
            maxImpact = impact; 
            res.clear();
            res.push_back(contraction[i]);
        }
        else if (impact == maxImpact)
            res.push_back(contraction[i]);
    }
    cout << maxImpact - 1 << endl; // Our definition of impact should exclude itself
    int n_maxImpact_Nodes = res.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n_maxImpact_Nodes; j++)
        {
            if (SCC[i] == SCC[res[j]])
            {
                cout << i << " ";
                break;
            }
        }
    }
#ifndef OJ
    system("pause");
#endif
    return 0;
}