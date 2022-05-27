#include<iostream>
#include<vector>
#include<limits.h>
//#define OJ
using namespace std;

class UnionFindSets
{
private:
    int *parent;
public:
    UnionFindSets(int n) { parent = new int[n]; for (int i = 0; i < n;i++) parent[i] = -1; };
    ~UnionFindSets() { delete parent; }
    int Find(int i) // Collapsing Find
    {
        int root;
        for (root = i; parent[root] >= 0; root = parent[root]);
        while (i != root)
        {
            int temp = parent[i];
            parent[i] = root;
            i = temp;
        }
        return root;
    }
    void UnionSet(int a, int b) // Weighted Union
    {
        int rootA = Find(a), rootB = Find(b);
        if (rootA == rootB)
            return;
        int temp = parent[rootA] + parent[rootB];
        //cout << parent[rootA] << " " << parent[rootB] << endl;
        if (parent[rootA] < parent[rootB]) {
            parent[rootB] = rootA;
            parent[rootA] = temp;
        }
        else {
            parent[rootA] = rootB;
            parent[rootB] = temp;
        }
    }
};

int main()
{
    int n, m, u, v, road_count;
    cin >> n >> m;
    UnionFindSets UF(n * 2);
    road_count = n - 1; // Minimum roads sto get connection
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        if (UF.Find(u) != UF.Find(v))
        {
            UF.UnionSet(u, v);
            road_count--;
        }
    }
    cout << road_count << endl;
#ifndef OJ
    system("pause");
#endif
    return 0; 
}