/*
 * @lc app=leetcode.cn id=1489 lang=cpp
 *
 * [1489] 找到最小生成树里的关键边和伪关键边
 */
#include<string>
#include<vector>
#include<numeric>
#include<algorithm>
#include<unordered_map>
using namespace std;
// @lc code=start

class UnionFind {
public:
    vector<int> parent;
    vector<int> size;
    int n;
    int setCount;
    UnionFind(int _n): n(_n), parent(_n), size(_n, 1), setCount(_n) {
        iota(parent.begin(), parent.end(), 0);
    }
    int Find(int x) // Collapsing Find by recursion
    { return parent[x] == x ? x : parent[x] = Find(parent[x]); }

    bool UnionSet(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y)
            return false;
        else {
            if (size[x] < size[y])
                swap(x, y);
            parent[y] = x;
            size[x] += size[y];
            setCount--;
            return true;
        }
    }
};

class TarjanSCC {
private:
    const vector<vector<int>>& edges;
    const vector<vector<int>>& edgesId;
    vector<int> back;
    vector<int> discoverTime;
    vector<int> bridge;
    int n;
    int time;

    void DFS(int u, int parentEdgeID) {
        back[u] = discoverTime[u] = time++;
        for (int i = 0; i < edges[u].size(); i++) {
            int v = edges[u][i];
            int EdgeID = edgesId[u][i];
            if (discoverTime[v] == -1)
            {
                DFS(v, EdgeID);
                back[u] = min(back[u], back[v]);
                if (back[v] > discoverTime[u])
                    bridge.emplace_back(EdgeID);
            }
            // MULTIPLE EDGE appears in our condensation graph, 
            // so judge BE by EdgeID instead of parent node ID!!!
            // Wrong Version: else if (v != parent) {
            else if (EdgeID != parentEdgeID) {
                back[u] = min(back[u], discoverTime[v]);
            }
        }
    }
public:
    TarjanSCC(vector<vector<int>>& _edges, vector<vector<int>>& _edgesId, int _n): 
    edges(_edges), edgesId(_edgesId), n(_n), time(0), back(_n, -1), discoverTime(_n, -1) {}

    vector<int> GetBridge() {
        for (int i = 0; i < n; i++)
            if (discoverTime[i] == -1)
                DFS(i, -1);
        return bridge;
    }
};

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        for (int i = 0; i < m; i++)
            edges[i].emplace_back(i); // Edge ID
        sort(edges.begin(), edges.end(), [] (const vector<int>& a, const vector<int>& b) { return a[2] < b[2]; });
        UnionFind UF(n);
        vector<vector<int>> result(2);
        vector<int> EdgeType(m, 0); // 0: Non-Bridge ; 1: Bridge ; -1: Cycle(Excluded from MST)
        for (int i = 0; i < m; )
        {
            int j = i; // All edges with index[i, j] have same weight
            while (j < m && edges[j][2] == edges[i][2])
                j++;
            unordered_map<int, int> CC2id;
            int n_Condensation = 0; // index of Connected Components
            /* By using Union Find, we could get a condensation graph of the subgraph 
            induced by edges with same weight w
            */
            for (int k = i; k < j; k++) {
                int x = edges[k][0];
                int y = edges[k][1];
                int xCC = UF.Find(x);
                int yCC = UF.Find(y);
                if (xCC == yCC)
                    EdgeType[edges[k][3]] = -1;
                else {
                    if (!CC2id.count(xCC))
                        CC2id[xCC] = n_Condensation++;
                    if (!CC2id.count(yCC))
                        CC2id[yCC] = n_Condensation++;
                }
            }
            vector<vector<int>> edgesCondensation(n_Condensation);
            vector<vector<int>> edgesID(n_Condensation);
            for (int k = i; k < j; k++) {
                int xCC = UF.Find(edges[k][0]);
                int yCC = UF.Find(edges[k][1]);
                if (xCC != yCC) {
                    int idx = CC2id[xCC];
                    int idy = CC2id[yCC];
                    edgesCondensation[idx].emplace_back(idy);
                    edgesID[idx].emplace_back(edges[k][3]);
                    edgesCondensation[idy].emplace_back(idx);
                    edgesID[idy].emplace_back(edges[k][3]);
                }
            }
            vector<int> bridge = TarjanSCC(edgesCondensation, edgesID, n_Condensation).GetBridge();
            for (int id : bridge) {
                result[0].emplace_back(id);
                EdgeType[id] = 1;
            }
            for (int k = i; k < j; k++) {
                UF.UnionSet(edges[k][0], edges[k][1]);
            }
            i = j;
        }
        for (int i = 0; i < m; i++)
            if (!EdgeType[edges[i][3]])
                result[1].emplace_back(edges[i][3]);
        return result;
    }
};

int main()
{
    vector<vector<int>> edges = {{0,1,2},{0,2,5},{2,3,5},{1,4,4},{2,5,5},{4,5,2}};
    Solution sol;
    vector<vector<int>> result = sol.findCriticalAndPseudoCriticalEdges(6, edges);
}
// @lc code=end

