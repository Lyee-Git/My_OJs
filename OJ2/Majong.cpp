#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;
//#define OJ

int main()
{
    int N;
    cin >> N;
    int *cards = new int[N];
    unordered_map<int, int> index;
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> cards[i];
        index[cards[i]] = i;
    }
    for (int i = 0; i < N; i += 2)
    {
        int pair = cards[i] % 2 ? cards[i] - 1 : cards[i] + 1;
        if (cards[i + 1] != pair)
        {
            int pair_idx = index[pair];
            swap(index[cards[i + 1]], index[cards[pair_idx]]);
            swap(cards[i + 1], cards[pair_idx]);
            cnt++;
        }
    }
    cout << cnt << endl;
    delete[] cards;
#ifndef OJ
    system("pause");
#endif
    return 0;
}