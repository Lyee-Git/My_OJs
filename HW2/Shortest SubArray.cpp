#include<iostream>
using namespace std;
#define OJ

int main()
{
    int N, target, i = 0;
    int *nums = new int[1000000];
    int sum = 0, digits = 0, min = 0;
    cin >> N;
    while (N--)
        cin >> nums[i++];
    cin >> target;
    for (int j = 0; j < i; j++)
    {
        sum += nums[j];
        digits++;
        if (sum >= target)
        {
            int begin = j - digits + 1;
            do
            {
                sum -= nums[begin++];
                digits--;
            } while (sum >= target);
            if (min > digits + 1 || !min)
                min = digits + 1;
        }
    }
    cout << min << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}