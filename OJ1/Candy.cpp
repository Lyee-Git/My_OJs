#include<vector>
#include<iostream>
#include<limits.h>
//#define OJ
using namespace std;

int main()
{
    vector<int> scores;
    int tmp;
    while (cin >> tmp)
        scores.emplace_back(tmp);
    int len = scores.size(), temp = 1, res = 0;
    vector<int> flower(len);
    flower[0] = 1;
    for (int i = 1; i < len; i++)
    {
        if (scores[i] > scores[i - 1])
            flower[i] = flower[i - 1] + 1;
        else   
            flower[i] = 1;
    }
    for (int i = len - 2; i >= 0; i--)
    {
        if (scores[i] > scores[i + 1])
            temp++;
        else   
            temp = 1;
        if (temp > flower[i])
            flower[i] = temp;
    }
    for (auto it : flower)
        res += it;
    cout << res << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;  
}