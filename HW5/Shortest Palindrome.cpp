#include<iostream>
#include<string>
using namespace std;
//#define OJ
// KMP

void buildNext(int *next, string P)
{
    int len = P.length() + 1, j = 0; // One more char than usual to get length of same prefix & suffix of string P
    int i = next[0] = -1; // i : pointer of pattern
    while (j < len - 1)
    {
        if (i < 0 || P[i] == P[j])
        {
            i++; j++;
            next[j] = i;
        }
        else
            i = next[i];
    }
}

int main()
{
    string T;
    cin >> T;
    int res = 0, *next = new int[2 * T.length() + 1], len = T.length();
    string T_add_reverse(T);
    for (int i = 0; i < len; i++)
        T_add_reverse.push_back(T[len - 1 - i]);
    buildNext(next, T_add_reverse);
    res = len - next[2 * len];
    cout << res << endl;
    delete[] next;
#ifndef OJ
    system("pause");
#endif
    return 0;
}