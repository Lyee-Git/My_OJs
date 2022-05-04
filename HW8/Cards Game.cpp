#include<iostream>
//#define OJ
using namespace std;
using LLong = long long;

void Merge(LLong *Array, int lo, int mi, int hi) // Reversely Sorting
{
    LLong *A = Array + lo, *C = Array + mi;
    int lb = mi - lo, lc = hi - mi;
    LLong *B = new LLong[lb];
    for (int i = 0; i < lb; i++)
        B[i] = A[i];
    for (int i = 0, j = 0, k = 0; j < lb; )
    {
        if (k >= lc || B[j] >= C[k])
            A[i++] = B[j++];
        else if (k < lc && B[j] < C[k])
            A[i++] = C[k++];
    }
    delete[] B;
}

void MergeSort(LLong* Array, int lo, int hi)
{   
    if (hi - lo < 2)
        return;
    int mi = (lo + hi) >> 1;
    MergeSort(Array, lo, mi);
    MergeSort(Array, mi, hi);
    Merge(Array, lo, mi, hi);
}

int main()
{
    int N, temp;
    cin >> N;
    int A[N], B[N];
    LLong *SumValues = new LLong[N];
    for (int i = 0; i < N; i++)
        cin >> A[i];
    for (int i = 0; i < N; i++)
    {
        cin >> B[i];
        SumValues[i] = ((A[i] + B[i]) << 17) + i;
    }
    MergeSort(SumValues, 0, N);
    int sum[2] = {0};
    for (int i = 0; i < N; i++)
        sum[i % 2] += i % 2 == 0 ? A[SumValues[i] & 0x1ffff] : B[SumValues[i] & 0x1ffff];
    if (sum[0] == sum[1])
        cout << "0" << endl;
    else if (sum[0] > sum[1])
        cout << "1" << endl;
    else
        cout << "-1" << endl;
    delete[] SumValues;
#ifndef OJ
    system("pause");
#endif
    return 0;
}