#include<iostream>
#include<limits.h>
//#define OJ
using namespace std;
struct Edge {			  
    int dest;				  
   	int cost;				   
   	Edge *link;		  
   	Edge () { dest = 0; }				   
   	Edge (int _num, int _cost): dest (_num), cost (_cost), link (nullptr) {}
   	bool operator != (Edge& R) const  { return dest != R.dest; }	
    void insertEdge(int _dest, int _cost)
    {
        Edge *e = this;
        while (e->link != nullptr)
            e = e->link;
        e->link = new Edge(_dest, _cost);
    }
};

long long maxPath = 0;
void DFS(Edge *tree, int i, int *vis, long long pathLength)
{
    vis[i] = 1;
    Edge *e = &(tree[i]);
    if (e->dest == 0)
        return;
    while (e != nullptr)
    {
        if (!vis[e->dest])
        {
            pathLength += e->cost;
            maxPath = max(maxPath, pathLength);
            DFS(tree, e->dest, vis, pathLength);
            pathLength -= e->cost;
        }
        e = e->link;
    }
}

int main()
{
    int n;
    cin >> n;
    Edge *tree = new Edge[n + 1];
    long long sumCost = 0;
    for (int i = 0; i < n - 1; i ++)
    {
        int from, to, w;
        cin >> from >> to >> w;
        sumCost += w;
        if (tree[from].dest == 0)
            tree[from] = Edge(to, w);
        else
            tree[from].insertEdge(to, w);
        if (tree[to].dest == 0)
            tree[to] = Edge(from, w);
        else
            tree[to].insertEdge(from, w);
    }
    int vis[n + 1] = {0};
    DFS(tree, 1, vis, 0);
    cout << 2 * sumCost - maxPath << endl;
    delete[] tree;
#ifndef OJ
    system("pause");
#endif
    return 0; 
}