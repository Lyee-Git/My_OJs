#include<iostream>
#include<limits.h>
//#define OJ
using namespace std;

void QuickSort(int *s, int lo, int hi)
{
    if (lo >= hi)
        return;
    int i = lo, j = hi;
    int pivot = s[lo];
    while (lo < hi)
    {
        while (lo < hi)
        {
            if (s[hi] > pivot)
                hi--;
            else
            {
                s[lo++] = s[hi]; break;
            }
        }
        while (lo < hi)
        {
            if (s[lo] < pivot)
                lo++;
            else
            {
                s[hi--] = s[lo]; break;
            }
        }
    }
    s[lo] = pivot;
    QuickSort(s, i, lo - 1);
    QuickSort(s, lo + 1, j);
}

int main()
{
    int N, M;
    long long sum = 0, remain = 0;
    cin >> N >> M;
    int *elem = new int[N];
    for (int i = 0; i < N; i++)
    {   
        cin >> elem[i];
        sum += elem[i];
    }
    QuickSort(elem, 0, N - 1);
    int V = elem[N - 1], cnt = 0;
    while (remain < M)
    {
        while (elem[N - 1 - cnt] >= V)
            cnt++;
        V--;
        remain += cnt;
    }
    cout << V << endl;
    delete[] elem;
#ifndef OJ
    system("pause");
#endif
    return 0; 
}