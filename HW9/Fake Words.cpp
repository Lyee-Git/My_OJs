#include<iostream>
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
    int N, K, a, b, count = 0;
    cin >> N >> K;
    UnionFindSets UF(3 * N);
    for (int i = 0; i < K; i++)
    {
        cin >> a >> b;
        if (a == b || a > N || b > N)
        { count++; continue; }
        if (UF.Find(b) == UF.Find(a + N) || UF.Find(a) == UF.Find(b))
        { count++; continue; }
        UF.UnionSet(a, b + N); // a beats b
        UF.UnionSet(a + N, b + 2 * N);
        UF.UnionSet(a + 2 * N, b);
    }
    cout << count << endl;
#ifndef OJ
    system("pause");
#endif
    return 0; 
}