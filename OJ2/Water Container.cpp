#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;
//#define OJ

int main()
{
    int n, m; 
    cin >> n;
    int *capacity = new int[n], *water= new int[n];
    memset(water, 0, sizeof(int) * n);
    for (int i = 0; i < n; i++)
        cin >> capacity[i];
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int type, num, volume;;
        cin >> type;
        if (type == 1)
        {
            cin >> num >> volume;
            int spill = volume, remaining;
            for (int j = num - 1; j < n && spill > 0; j++)
            {
                remaining = capacity[j] - water[j];
                if (spill > remaining) {
                    spill -= remaining;
                    water[j] += remaining;
                }
                else {
                    water[j] += spill;
                    spill = 0;
                }
            }
        }
        else {
            cin >> num;
            cout << water[num - 1] << endl;
        }
    }
    delete[] capacity; delete[] water;
#ifndef OJ
    system("pause");
#endif
    return 0;
}