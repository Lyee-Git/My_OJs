#include<iostream>
#include<limits.h>
using namespace std;
//#define OJ
struct node
{
    int *edge;
    int val, degeree, father, indexSum;
    node(int _val = 0): edge(new int[100]), val(_val), degeree(0), father(0), indexSum(0) {}
    ~node() { delete[] edge; }
    void addEdge(int _val) { edge[degeree++] = _val; }
};

void DFS(node *tree, int u)
{
    for (int i = 0; i < tree[u].degeree; i++)
    {
        int v = tree[u].edge[i];
        if (v != tree[u].father)
        {
            tree[v].father = u;
            DFS(tree, v);
            if (tree[v].indexSum > 0)
                tree[u].indexSum += tree[v].indexSum;
        }
    }
}

int main()
{
    int N, temp, u, v, root, max_sum = INT_MIN;
    cin >> N;
    node tree[N + 1];
    for (int i = 1; i <= N; i++)
    {
        cin >> temp;
        tree[i].val = tree[i].indexSum = temp;
    }
    for (int i = 0; i < N - 1; i++)
    {
        cin >> u >> v;
        if (!i)
            root = u;
        tree[u].addEdge(v);
        tree[v].addEdge(u);
    }
    DFS(tree, root);
    for (int i = 1; i <= N; i++)
        max_sum = max(max_sum, tree[i].indexSum);
    cout << max_sum << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}