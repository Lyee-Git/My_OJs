#include<iostream>
#include<limits.h>
using namespace std;
//#define OJ

template<class T>
class Heap
{
public:
    Heap(int n): HeapSize(0) { elem = new T[n]; };
    Heap (int *array, int n) { elem = array; HeapSize = n; Heapify(); }
    ~Heap() { delete[] elem; }
    void insert(T );
    T delMax();
    T getMax();
    void Popk(int k);
    bool isEmpty();
    int size();
private:
    T *elem;
    int HeapSize;
    void percolateDown(int i);
    void percolateUp(int i);
    void Heapify();
};

template<class T> void Heap<T>::percolateDown(int i)
{
    int lc = 2 * i + 1, rc = 2 * i + 2, j = i;
    if (lc < HeapSize && elem[lc] < elem[i])
        j = lc;
    if (rc < HeapSize && elem[rc] < elem[lc] && elem[rc] < elem[i])
        j = rc;
    if (j != i)
    {
        swap(elem[i], elem[j]);
        percolateDown(j);
    }
}

template<class T> void Heap<T>::percolateUp(int i)
{
    while (i > 0)
    {
        int j = (i - 1) >> 1;
        if (elem[i] < elem[j])
        {
            swap(elem[i], elem[j]);
            i = j;
        }
        else
            break;
    }
}

template<class T> void Heap<T>::Heapify()
{
    for (int i = ((HeapSize - 1) - 1) >> 1; i >= 0; i--)
        percolateDown(i);
}

template<class T> void Heap<T>::insert(T e)
{
    elem[HeapSize] = e;
    percolateUp(HeapSize++);
}

template<class T> T Heap<T>::delMax()
{
    T max = elem[0];
    elem[0] = elem[--HeapSize];
    percolateDown(0);
    return max;
}

template<class T> T Heap<T>::getMax(){ return elem[0]; }

template<class T> void Heap<T>::Popk(int k)
{
    if (!k)
        return;
    T top = delMax();
    Popk(--k);
    cout << top << " ";
}

template<class T> bool Heap<T>::isEmpty() { return HeapSize == 0; }

template<class T> int Heap<T>::size() { return HeapSize; }

struct edge
{
    int product; // 时间和战力的乘积
    int time, combat; // 时间和战力
    int nodeNum;
    edge (int _time = 0, int _combat = 0, int _nodeNum = 0) : time(_time), combat(_combat), product(_time * _combat), nodeNum(_nodeNum) {}
    bool operator<(const edge& another) { return product < another.product; }
};

struct node
{
    edge *neighbor;
    int val, degeree, father;
    node(int _val = 0): neighbor(new edge[10]), val(_val), degeree(0), father(0) {}
    ~node() { delete[] neighbor; }
    void addEdge(edge _val) { neighbor[degeree++] = _val; }
};

long long Dijstra(node *graph, int src, int end, int n) 
{
    long long *minDist = new long long[n];
    int *visited = new int[n], MAX_INT = INT_MAX - 100000000;
    for (int i = 1; i < n; i++) {
        minDist[i] = MAX_INT;
        visited[i] = 0;
    }
    Heap<edge> MinHeap(100000);
    MinHeap.insert(edge(0, 0, src));
    minDist[src] = 0;
    while (!MinHeap.isEmpty()) {
        edge e = MinHeap.getMax();
        MinHeap.delMax();
        int u = e.nodeNum, prev_time = e.time, prev_combat = e.combat;
        if (visited[u])
            continue;
        visited[u] = 1; // Finished
        for (int i = 0; i < graph[u].degeree; i++) {
            int v = graph[u].neighbor[i].nodeNum;
            int cur_time = graph[u].neighbor[i].time + prev_time; // 加入边后新的时间
            int cur_combat = graph[u].neighbor[i].combat + prev_combat; // 加入边后新的战力
            int new_product = cur_time * cur_combat; // 动态更新乘积
            if (!visited[v] && new_product < minDist[v]) { // 根据乘积做松弛
                minDist[v] = new_product;
                MinHeap.insert(edge(cur_time, cur_combat, v)); // Add v to Fringe or change v in Fringe
            }
        }
    }
    long long result = minDist[end];
    delete[] visited; delete[] minDist;
    return result;
}

int main()
{
    int n, m, src, end;
    cin >> n >> m >> src >> end;
    node *graph = new node[(m + 1) * n + 1];
    for (int i = 1; i <= n; i++) {
        delete[] graph[i].neighbor;
        graph[i].neighbor = new edge[1000];
    }
    int *switchCost = new int[m + 1], *nodesCnt = new int[m + 1];
    for (int i = 1; i <= m; i++) 
        cin >> nodesCnt[i];
    for (int i = 1; i <= m; i++) 
        cin >> switchCost[i];
    for (int i = 1; i <= m; i++) {
        int p = nodesCnt[i];
        int lineNodes[p];
        int time[p - 1];
        int present[n + 1] = {0};
        for (int j = 0; j < p; j++) {
            int lineNodenum;
            cin >> lineNodenum;
            lineNodes[j] = lineNodenum;
            if (!present[lineNodenum]) {
                graph[lineNodenum].addEdge(edge(switchCost[i], 0, i * n + lineNodenum));
                graph[i * n + lineNodenum].addEdge(edge(0, 0, lineNodenum));
                present[lineNodenum] = 1;
            }
        }
        for (int j = 0; j < p - 1; j++) 
            cin >> time[j];
        for (int j = 0; j < p - 1; j++) {
            int combat;  cin >> combat;
            graph[i * n + lineNodes[j]].addEdge(edge(time[j], combat, i * n + lineNodes[j + 1]));
        }
    }
    long long result = Dijstra(graph, src, end, (m + 1) * n + 1);
    cout << result << endl;
    delete[] graph; delete[] switchCost; delete[] nodesCnt;
#ifndef OJ
    system("pause");
#endif
    return 0;
}

