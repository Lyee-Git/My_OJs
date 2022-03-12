#include<iostream>
#include<string>
using namespace std;
//#define OJ
long cnt = 0;

void Merge(string* Array, string* B, int lo, int mi, int hi)
{
    string *A = Array + lo;
    int lb = mi - lo, lc = hi - mi;
    for (int i = 0; i < lb; i++)
        B[i] = A[i];
    string *C = Array + mi;
    for (int i = 0, j = 0, k = 0; j < lb; )
    {
        if (k >= lc || B[j] <= C[k]) // Short-circuit evaluation
            A[i++] = B[j++];
        else if (k < lc && B[j] > C[k])
        {
            A[i++] = C[k++];
            cnt += lb - j;  // Inversions: (j ~ lb - 1, k)
        }
    }
}

void MergeSort(string* Array, string* B, int lo, int hi)
{   
    if (hi - lo < 2)
        return;
    int mi = (lo + hi) >> 1;
    MergeSort(Array, B, lo, mi);
    MergeSort(Array, B, mi, hi);
    Merge(Array, B, lo, mi, hi);
}

int main()
{
    long n_words = 0;
    cin >> n_words;
    string *words = new string[n_words], *B = new string[n_words >> 1];
    for (int i = 0; i < n_words; i++)
        cin >> words[i];
    MergeSort(words, B, 0, n_words);
    cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
    cout << cnt << endl;
    delete[] words;
    delete[] B;
#ifndef OJ
    system("pause");
#endif
    return 0;
}