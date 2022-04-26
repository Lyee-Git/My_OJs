#include<vector>
#include<iostream>
#include<stack>
#include<limits.h>
//#define OJ
using namespace std;

bool findPattern(int *nums, int N)
{
    stack<int> sta;
    // find x < y < z such that ax < az < ay
    int z_candidate = INT_MIN;
    sta.push(nums[N - 1]);
    for (int i = N - 2; i >= 0; i--)
    {
        if (!sta.empty() && sta.top() > nums[i])
        {
            if (z_candidate > nums[i])
                return true;
            sta.push(nums[i]);
        }
        else
        {
            while (!sta.empty() && sta.top() < nums[i])
            {
                if (sta.top() > z_candidate)
                    z_candidate = sta.top();
                sta.pop();
            }
            sta.push(nums[i]);
        }
    }
    return false;
}

int main()
{
    int N;
    cin >> N;
    int nums[N];
    for (int i = 0; i < N; i++)
        cin >> nums[i];
    bool res = findPattern(nums, N);
    if (res)
        cout << "True" << endl;
    else
        cout << "False" << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;     
}