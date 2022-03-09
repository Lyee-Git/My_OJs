#include<iostream>
using namespace std;
#define OJ

int main()
{
    int n, x, cnt = 0, digit = 1;
    cin >> n >> x;
    int k = n;
    while (k /= 10)
        digit++;
    if (!x)
        digit--;
    for (int i = 1, j = 0; j < digit; i *= 10, j++)
    {
        int temp = n / (i * 10);
        if (!x)
            temp--;
        cnt += temp * i;
        int last = n / i % 10;
        if (last > x)
            cnt += i;
        else if (last == x)
            cnt += n % i + 1;
    }
    cout << cnt << endl;
    #ifndef OJ
        system("pause");
    #endif
    return 0;
}