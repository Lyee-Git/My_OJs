#include<iostream>
#include<vector>
#include<algorithm>
#include<limits.h>
#include<unordered_map>
#include<queue>
//#define OJ
using namespace std;

int main()
{
    int N, M, u, v, w;
    cin >> N >> M;
    vector<int> weight;
    vector<vector<int>> edges;
    for (int i = 0; i < N; i++) {
        cin >> w;
        weight.emplace_back(w);
    }
    for (int i = 0; i < M; i++) {
        cin >> u >> v;
        vector<int> a;
        a.emplace_back(u); a.emplace_back(v);
        edges.emplace_back(a);
    }
    vector<unordered_map<int, int>> graph(N);
    sort(edges.begin(), edges.end(), [&](vector<int> &a, vector<int> &b){
        return weight[a[0]] + weight[a[1]] > weight[b[0]] + weight[b[1]];
    });
    for (int i = 0; i < M; ++i) {
        int u = edges[i][0], v = edges[i][1];
        graph[u][v] = i;
        graph[v][u] = i;
    }
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        unordered_map<int, int> &neighbor = graph[i];
        vector<int> pos;
        int degree = neighbor.size();
        // Find Triangle
        for (auto [j, ji] : graph[i])
            for (auto [k, ki] : graph[i]) {
                if (j != k && graph[j].count(k))
                    pos.emplace_back(graph[j][k]);
            }
        priority_queue<int> pq;
        for (int j : pos) {
            if (pq.size() < 3 || j < pq.top())
                pq.push(j);
            if (pq.size() > 3)
                pq.pop();
        }
        while (!pq.empty()) {
            auto &a = edges[pq.top()];
            int x = a[0], y = a[1];
            int sum = weight[i] + weight[x] + weight[y];
            pq.pop();
            for (int j : pos) {
                int cur_sum = sum;
                auto& e = edges[j];
                int v = e[0], w = e[1];
                if (v != x && v != y)
                    cur_sum += weight[v];
                if (w != x && w != y)
                    cur_sum += weight[w];
                ans = max(ans, cur_sum);
            }
        }   
    }
    cout << ans << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}