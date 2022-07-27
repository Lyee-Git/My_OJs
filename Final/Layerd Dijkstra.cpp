#include<iostream>
#include<limits.h>
using namespace std;
//#define OJ
using edge = pair<int, int>; // <to, weight>

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

int Dijstra(node *graph, int src, int end, int n) 
{
    int *minDist = new int[n]; // 记录每个节点到源点的最小距离
    int *visited = new int[n];
    for (int i = 0; i < n; i++) {
        minDist[i] = INT_MAX / 2;
        visited[i] = 0;
    }
    Heap<edge> MinHeap(100000);
    MinHeap.insert(make_pair(0, src)); // 将源点加入堆中
    minDist[src] = 0;
    while (!MinHeap.isEmpty()) {
        edge e = MinHeap.getMax();
        MinHeap.delMax();
        int u = e.second;
        if (visited[u])
            continue;
        visited[u] = 1; // Finished
        for (int i = 0; i < graph[u].degeree; i++) {
            int v = graph[u].neighbor[i].second, weight = graph[u].neighbor[i].first;
            if (!visited[v] && minDist[u] + weight < minDist[v]) { // 松弛
                minDist[v] = minDist[u] + weight;
                MinHeap.insert(make_pair(minDist[v], v)); // Add v to Fringe or change v in Fringe
            }
        }
    }
    int result;
    if (minDist[end] == INT_MAX / 2)
        result = -1;
    else 
        result = minDist[end];
    delete[] visited;
    delete[] minDist;
    return result;
}

int main()
{
    int n, m, src, end;
    cin >> n >> m >> src >> end;
    node *graph = new node[(m + 1) * n]; // m X n个虚节点和 n 个原节点
    // 其中 0 ~ n 对应原节点，之后每n个对应一条线路上的n个虚节点
    for (int i = 0; i < n; i++) {
        delete[] graph[i].neighbor;
        graph[i].neighbor = new edge[200];
    }
    for (int i = 1; i <= m; i++) {
        int p; // 读入该交通线途径的国家数量p
        cin >> p;
        int lineNodes[p];
        for (int j = 0; j < p; j++) {
            int lineNodenum;
            cin >> lineNodenum;
            lineNodes[j] = lineNodenum;
            graph[lineNodenum].addEdge(make_pair(0, i * n + lineNodenum)); // 每条线路对应的虚节点与0 ~n范围内对应的国家节点（原节点）相连，权值为零
            graph[i * n + lineNodenum].addEdge(make_pair(0, lineNodenum));
        }
        for (int j = 0; j < p - 1; j++) { // 读入权值
            int weight;
            cin >> weight;
            graph[i * n + lineNodes[j]].addEdge(make_pair(weight, i * n + lineNodes[j + 1])); // 若线路上这两个国家相连，则这两个国家所在线路的虚节点相连
            graph[i * n + lineNodes[j + 1]].addEdge(make_pair(weight, i * n + lineNodes[j]));
        }
    }
    int result = Dijstra(graph, src, end, (m + 1) * n);
    cout << result << endl;
    delete[] graph;
#ifndef OJ
    system("pause");
#endif
    return 0;
}

