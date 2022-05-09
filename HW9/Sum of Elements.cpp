#include<iostream>
#include<unordered_map>
#include<limits.h>
//#define OJ
using namespace std;

int main()
{
    int n, a, b;
    cin >> n >> a >> b;
    int *coins = new int[n], *Match = new int[n], *Train = new int[n]; // Match: num of matches
    int sum[2] = {a, b};
    unordered_map<int, int> index;
    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
        index[coins[i]] = i;
        Match[i] = 0; Train[i] = -1;
    }
    for (int i = 0; i < n;i++)
    {
        if (index.count(a - coins[i]))
            Match[i]++;
        if (index.count(b - coins[i]))
            Match[i]++;
    }
    for (int i = 0; i < n; i++)
    {
        if (Train[i] == -1)
        {
            if (index.count(a - coins[i]) &&  Train[index[a - coins[i]]] == -1)
            {
                int index_a = index[a - coins[i]]; // Take train A with i
                Match[i]--; 
                if (i != index_a) // check if i teams up with itself
                    Match[index_a]--;
                Train[i] = Train[index_a] = 0;
                continue;
            }
            if (index.count(b - coins[i]) && Train[index[b - coins[i]]] == -1)
            {
                int index_a = index[b - coins[i]]; // Take train B with i
                Match[i]--; 
                if (i != index_a) 
                    Match[index_a]--;
                Train[i] = Train[index_a] = 1;
                continue;
            }
            if (index.count(a - coins[i]) && Train[index[a - coins[i]]] != -1)
            {
                int index_a = index[a - coins[i]]; // index_a Could possibly Take train A with i or Take train B with i
                // But index_a already has a partner index_b, We 'll check if index_b has another possible partner index_c
                int sum_train_ab = sum[Train[index_a]]; // Sum of Train a & b take
                int index_b = index[sum_train_ab - coins[index_a]]; // Take Train train_ab with index_a
                if (Match[index_b] > 0) // If index_c exists, Reschedule the match
                {
                    int sum_train_bc = sum[!Train[index_a]]; // Sum of Train that b & c will alter to take
                    int index_c = index[sum_train_bc - coins[index_b]];
                    if (Train[index_c] == -1)
                    {
                        Match[index_b]--; 
                        if (index_b != index_c)
                            Match[index_c]--;
                        Train[index_b] = Train[index_c] = !Train[index_a];
                        Train[i] = Train[index_a] = !Train[index_a];
                        continue;
                    }
                }
            }
            if (index.count(b - coins[i]) && Train[index[b - coins[i]]] != -1)
            {
                int index_a = index[b - coins[i]];
                int sum_train_ab = sum[Train[index_a]]; // Sum of Train a & b take
                int index_b = index[sum_train_ab - coins[index_a]]; // Take Train train_ab with index_a
                if (Match[index_b] > 0) // If index_c exists, Reschedule the match
                {
                    int sum_train_bc = sum[!Train[index_a]]; // Sum of Train that b & c will alter to take
                    int index_c = index[sum_train_bc - coins[index_b]];
                    if (Train[index_c] == -1)
                    {
                        Match[index_b]--; 
                        if (index_b != index_c)
                            Match[index_c]--;
                        Train[index_b] = Train[index_c] = !Train[index_a];
                        Train[i] = Train[index_a] = !Train[index_a];
                        continue;
                    }
                }
            }
        }
    }
    bool success = true;
    for (int i = 0; i < n; i++) {
        if (Train[i] == -1)
            success = false;
    }
    if (!success) 
        cout << "0" << endl;
    else {
        cout << "1" << endl;
        for (int i = 0; i < n - 1; i++) cout << Train[i] << " ";
        cout << Train[n - 1];
    }
    delete coins; delete Match; delete Train;
#ifndef OJ
    system("pause");
#endif
    return 0; 
}