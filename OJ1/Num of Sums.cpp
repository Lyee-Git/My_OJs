#include<iostream>
#include<unordered_map>
//#define OJ
#define SIZE 16341163
using namespace std;

int main()
{
    int N;
    cin >> N;
    int limit = N * N + N;
    //int sums[SIZE];
    unordered_map<int, bool> sums;
    int prefix = 0, res = 0;
    sums[0] = 1;
    for (int i = 1; i <= N / 2 + 1; i++)
    {
        prefix += i;
        sums[prefix] = 1;
        if (prefix - N >= 0 && sums.find(prefix - N) != sums.end()) //sums[(prefix - N) % SIZE] == 1)
            res++;
    }
    cout << res + 1 << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}