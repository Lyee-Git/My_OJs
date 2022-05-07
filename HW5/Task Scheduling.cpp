#include<iostream>
#include<vector>
#include<algorithm>
#include<limits.h>
//#define OJ
using namespace std;
enum Color {WHITE, GRAY, BLACK};

class node
{
public:
    vector<int> edge;
    Color col;
    int length, est, eft;
    node *CritDep;
    node(int _length = 0, Color _col = WHITE, int _est = 0, int _eft = 0): length(_length), col(_col), est(_est), eft(_eft), CritDep(nullptr) {}
};

void DFS(int x, node *Graph)
{
    node& u = Graph[x];
    u.col = GRAY;
    int n = u.edge.size();
    for (int i = 0; i < n; i++)
    {
        node& v = Graph[u.edge[i]];
        if (v.col == WHITE)
        {
            DFS(u.edge[i], Graph);
            if (v.eft >= u.est)
            {
                u.est = v.eft;
                u.CritDep = &v;
            }
        }
        else
            if (v.eft >= u.est)
            {
                u.est = v.eft;
                u.CritDep = &v;
            }
    }
    u.col = BLACK;
    u.eft = u.est + u.length;
}

int main()
{
    int n;
    cin >> n;
    int num, time, from, to;
    node* Graph = new node[n + 1];
    for (int i = 0; i < n; i++)
    {
        cin >> num >> time;
        Graph[num].length = time;
    }
    while (cin >> from >> to)
        Graph[from].edge.push_back(to);
    for (int i = 1; i < n + 1; i++)
    {
        if (Graph[i].col == WHITE)
            DFS(i, Graph);
    }
    int shortest_time = 0;
    for (int i = 1; i < n + 1; i++)
    {
        if (Graph[i].eft > shortest_time)
            shortest_time = Graph[i].eft;
    }
    cout << shortest_time << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}