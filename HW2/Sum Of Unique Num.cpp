#include<iostream>
using namespace std;

int main()
{
    int sum = 0, frequence[100] = {0}, num = 0;
    while (cin >> num)
    {
        frequence[num]++;
        sum += frequence[num] > 2 ? 0 : (frequence[num] == 2 ? -num : num);
    }
    cout << sum <<endl;
    return 0;
    //system("pause");
}