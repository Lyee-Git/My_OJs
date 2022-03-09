#include<iostream>
using namespace std;
#define OJ

int main()
{
    int elem, sum = 0, max = INT32_MIN;
    int record[10000];
    while (cin >> elem)
    {
        sum = sum < 0 ? elem : sum + elem;
        if (sum > max)
            max = sum;
    }
    cout << max << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}