#include<iostream>
#include<string>
using namespace std;
#define OJ

int main()
{
    string queue;
    cin >> queue;
    int boy = 0, girl = 0, len = queue.length(), j = 0;
    for (int i = 0; i < len; i++)
        girl += queue[i] - '0';
    //boy = len - girl;
    for (j = 0; j < len && boy != girl; j++)
    {
        if (queue[j] - '0')
            girl--;
        else
            boy++;
    }
    if (boy == girl)
        cout << j << endl;
    else
        cout << "-1" << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}