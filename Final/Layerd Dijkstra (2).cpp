#include<iostream>
#include<limits.h>
using namespace std;
//#define OJ
using edge = pair<long long, int>; // <to, weight>

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
    MinHeap.insert(make_pair(0, src));
    minDist[src] = 0;
    while (!MinHeap.isEmpty()) {
        edge e = MinHeap.getMax();
        MinHeap.delMax();
        int u = e.second;
        if (visited[u])
            continue;
        visited[u] = 1; // Finished
        for (int i = 0; i < graph[u].degeree; i++) {
            int v = graph[u].neighbor[i].second;
            long long weight = graph[u].neighbor[i].first;
            if (!visited[v] && minDist[u] + weight < minDist[v]) {
                minDist[v] = minDist[u] + weight;
                MinHeap.insert(make_pair(minDist[v], v)); // Add v to Fringe or change v in Fringe
            }
        }
    }
    long long result = minDist[end];
    delete[] visited;
    delete[] minDist;
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
    int *switchCost = new int[m + 1], *nodesCnt = new int[m + 1]; // 每条线路的转换耗费时间SwitchCost和节点数nodesCnt
    for (int i = 1; i <= m; i++) 
        cin >> nodesCnt[i];
    for (int i = 1; i <= m; i++) 
        cin >> switchCost[i];
    for (int i = 1; i <= m; i++) {
        int p = nodesCnt[i];
        int lineNodes[p];
        int present[n + 1] = {0}; // present用于标记虚节点到原节点是否已经相连
        for (int j = 0; j < p; j++) { // 读入线路上每个节点
            int lineNodenum;
            cin >> lineNodenum;
            lineNodes[j] = lineNodenum;
            if (!present[lineNodenum]) { // 确保虚节点到原节点还未相连，避免重复连接
                graph[lineNodenum].addEdge(make_pair(switchCost[i], i * n + lineNodenum)); // 原节点到虚节点连接边权值为切换到对应线路所耗费的时间
                graph[i * n + lineNodenum].addEdge(make_pair(0, lineNodenum)); // 离开不耗费时间，因此虚节点到原节点连接边权值为0
                present[lineNodenum] = 1;
            }
        }
        for (int j = 0; j < p - 1; j++) {
            int weight;
            cin >> weight;
            graph[i * n + lineNodes[j]].addEdge(make_pair(weight, i * n + lineNodes[j + 1])); // 两个相邻城市所在线路的虚节点相连，此时为单向边
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

