// Leetcode 56
#include<iostream>
#include<limits.h>
using namespace std;
//#define OJ

void sort(int (*Array)[2], int lo, int hi)
{
    if (lo >= hi)
        return;
    int i = lo, j = hi, pivot[2];
    pivot[0] = Array[lo][0]; pivot[1] = Array[lo][1];
    while (lo < hi)
    {
        while (lo < hi)
            if (Array[hi][0] > pivot[0])
                hi--;
            else    
            {
                Array[lo][0] = Array[hi][0]; Array[lo][1] = Array[hi][1]; 
                lo++; break; 
            }
        while (lo < hi)
            if (Array[lo][0] < pivot[0])
                lo++;
            else    
            {
                Array[hi][0] = Array[lo][0]; Array[hi][1] = Array[lo][1];
                hi--; break; 
            }
    }
    Array[lo][0] = pivot[0]; Array[lo][1] = pivot[1];
    sort(Array, i, lo - 1);
    sort(Array, hi + 1, j);
}

int main()
{
    int n_intervals, n_res = 0;
    cin >> n_intervals;
    int intervals[n_intervals][2], res[n_intervals][2];
    for (int i = 0; i < n_intervals; i++)
        cin >> intervals[i][0] >> intervals[i][1];
    sort(intervals, 0, n_intervals - 1);
    int lo = intervals[0][0], hi = intervals[0][1];
    for (int i = 0; i < n_intervals; i++)
    {
        if (intervals[i][0] <= hi)
        {   
            if (intervals[i][1] > hi)
                hi = intervals[i][1];
        }
        else
        {
            res[n_res][0] = lo;
            res[n_res++][1] = hi;
            lo = intervals[i][0];
            hi = intervals[i][1];
        }
    }
    res[n_res][0] = lo;
    res[n_res++][1] = hi;
    for (int i = 0; i < n_res; i++)
        cout << res[i][0] << " "  << res[i][1] << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}