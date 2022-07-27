#include<iostream>
#include<algorithm>
using namespace std;
//#define OJ

int main()
{
    int N, T, sum = 0, temp, salary = 0;
    cin >> N >> T;
    int *value = new int[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &value[i]);
        sum += value[i];
    }
    int base = (sum + T - 1) / T;
    for (int i = 0; i < N; i++)
        salary += (value[i] + base - 1) / base;
    int inc = base - 1;
    if ((sum + inc - 1) / inc < T) {
        while ((sum + inc - 1) / inc <= T)
            inc--;
        base = inc + 1;
    }
    while (salary > T) {
        base++;
        salary = (sum + base - 1) / base;
    }
    
    cout << base << endl;
    delete[] value;
#ifndef OJ
    system("pause");
#endif
    return 0;
}