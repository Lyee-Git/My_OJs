#include<iostream>
#include<vector>
#include<limits.h>
//#define OJ
using namespace std;
vector<vector<int>> map;
int row, col;
constexpr int orient_x[4] = {0, 0, 1, -1};
constexpr int orient_y[4] = {1, -1, 0, 0};

int DFS(int i, int j)
{
    if (i < 0 || i >= row || j < 0 || j >= col || !map[i][j])
        return 1;
    if (map[i][j] == INT_MAX) // Visited
        return 0;
    map[i][j] = INT_MAX;
    int result = 0;
    for (int m = 0; m < 4; m++)
            result += DFS(i + orient_x[m], j + orient_y[m]);
    return result;
}

int main()
{
    int temp, result = 0;
    cin >> row >> col;
    map.resize(row);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
            cin >> temp;
            map[i].emplace_back(temp);
        }
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (map[i][j] == 1)
                result += DFS(i, j);
    cout << result << endl;
#ifndef OJ
    system("pause");
#endif
    return 0; 
}