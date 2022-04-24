#include<iostream>
#include<stdio.h>
//#define OJ
using namespace std;

int findMedian(int *A, int *B, int n)
{
    int ptr_A = 0, ptr_B = 0, rank = n;  // rank: Find rank nth element in remaining two sorted array
    while (true)
    {
        if (rank == 1)
            return A[ptr_A] <= B[ptr_B] ? A[ptr_A] : B[ptr_B];
        int cmp_A = ptr_A + rank / 2 - 1;
        int cmp_B = ptr_B + rank / 2 - 1;
        if (cmp_A > n - 1)
            cmp_A = n - 1;
        if (cmp_B > n - 1)
            cmp_B = n - 1;
        if (A[cmp_A] >= B[cmp_B])
        {
            int offset = cmp_B - ptr_B + 1;
            rank -= offset;
            ptr_B = cmp_B + 1;
            if (ptr_B == n)
                return A[ptr_A + rank - 1];
        }
        else
        {
            int offset = cmp_A - ptr_A + 1;
            rank -= offset;
            ptr_A = cmp_A + 1;
            if (ptr_A == n)
                return B[ptr_B + rank - 1];
        }
    }
}

int main()
{
    int n;
    cin >> n;
    int A[n], B[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &B[i]);
    int median = findMedian(A, B, n);
    cout << median << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}