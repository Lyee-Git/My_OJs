#include<iostream>
#include<vector>
#include<algorithm>
#include<limits.h>
//#define OJ
using namespace std;

int _time = 1;
vector<int> ArticPoint;
vector<vector<int>> bridge;

struct node
{
    vector<int> edge;
    int back, discoverTime, father;
    int subTree; // num of subtrees that satisfies (graph[v].back >= graph[u].discoverTime), making node an ArticPoint
    node(int _back = 0, int _discoverTime = 0, int _father = 0, int _subTree = 0): back(_back), discoverTime(_discoverTime), father(_father), subTree(_subTree) {}
};

void DFS(int u, bool root, node *graph)
{
    graph[u].discoverTime = _time++;
    graph[u].back = graph[u].discoverTime;
    for (int i = 0; i < graph[u].edge.size(); i++)
    {
        int v = graph[u].edge[i];
        if (!graph[v].discoverTime)
        {
            graph[v].father = u;
            DFS(v, false, graph);
            if (graph[v].back >= graph[u].discoverTime)
                graph[u].subTree++;
            if (graph[v].back > graph[u].discoverTime)
                bridge.push_back({min(u, v), max(u, v)});
            graph[u].back = min(graph[u].back, graph[v].back);
        }
        else if (v != graph[u].father)
            graph[u].back = min(graph[u].back, graph[v].discoverTime);
    }
    if ((!root && graph[u].subTree >= 1) || (root && graph[u].subTree >= 2))
            ArticPoint.emplace_back(u);
}

int main()
{
    int n;
    cin >> n;
    node graph[n];
    int u, v;
    while (cin >> u >> v)
    {
        graph[u].edge.emplace_back(v);
        graph[v].edge.emplace_back(u);
    }
    DFS(1, true, graph);
    sort(ArticPoint.begin(), ArticPoint.end());
    sort(bridge.begin(), bridge.end());
    cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
    for (int i = 0; i < ArticPoint.size(); i++)
    {
        cout << ArticPoint[i] << endl;
    }
    for (int i = 0; i < bridge.size(); i++)
    {
        cout << bridge[i][0] << " " << bridge[i][1] << endl;
    }
#ifndef OJ
    system("pause");
#endif
    return 0;
}
