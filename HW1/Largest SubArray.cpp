#include<iostream>
using namespace std;
#define OJ

int main()
{
    int n_elem, sum = 0, max = INT32_MIN;
    int record[10000];
    cin >> n_elem;
    while (n_elem--)
    {
        int elem;
        cin >> elem;
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