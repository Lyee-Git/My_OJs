#include<iostream>
#include<limits.h>
//#define OJ
using namespace std;

//  Time: Worst case O(N^2) Space: Worst case O(N)
// When Tree degenerates to a linked list

int lower_bound(int *array, const int elem, int lo, int hi)
{
    while (lo < hi)
    {
        int mid = (lo + hi) >> 1;
        array[mid] > elem ? hi = mid : lo = mid + 1;
    }
    return lo;
}

bool checkBST(int *nodes, int lo, int hi)
{
    if (lo > hi)
        return true;
    int root = nodes[hi];
    int partition = lower_bound(nodes, root, lo, hi);
    bool left = true, right = true;
    for (int i = lo; i < partition; i++)
        if (nodes[i] >= root)
            left = false;
    for (int i = partition; i < hi; i++)
        if (nodes[i] <= root)
            right = false;
    return left && right && checkBST(nodes, lo, partition - 1) && checkBST(nodes, partition, hi - 1);
}

int main()
{
    int N;
    cin >> N;
    int *nodes = new int[N];
    for (int i = 0; i < N; i++)
        cin >> nodes[i];
    bool valid = checkBST(nodes, 0, N - 1);
    if (valid)
        cout << "1" <<endl;
    else
        cout << "0" <<endl;
    delete[] nodes;
#ifndef OJ
    system("pause");
#endif
    return 0; 
}