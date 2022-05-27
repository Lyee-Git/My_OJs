#include<iostream>
#include<limits.h>
#include<math.h>
//#define OJ
using namespace std;

template<class T>
class Heap
{
public:
    Heap(int n): HeapSize(0) { elem = new T[n]; };
    ~Heap() { delete[] elem; }
    void insert(T);
    void insert(int);
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
    if (lc < HeapSize && elem[lc] > elem[i])
        j = lc;
    if (rc < HeapSize && elem[rc] > elem[lc] && elem[rc] > elem[i])
        j = rc;
    if (j != i)
    {
        T temp = elem[i];
        elem[i] = elem[j];
        elem[j] = temp;
        percolateDown(j);
    }
}

template<class T> void Heap<T>::percolateUp(int i)
{
    while (i > 0)
    {
        int j = (i - 1) >> 1;
        if (elem[i] > elem[j])
        {
            T temp = elem[i];
            elem[i] = elem[j];
            elem[j] = temp;
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

template<class T> void Heap<T>::insert(int e) { insert(T(e)); }

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

struct Edge {			  
    int dest;				  
   	int cost;				   
   	Edge *link;		  
   	Edge (): dest (-1), cost (0), link (nullptr) {}	   
   	Edge (int _num, int _cost): dest (_num), cost (_cost), link (nullptr) {}
   	bool operator != (Edge& R) const  { return dest != R.dest; }	   
    bool operator > (const Edge& another) { return cost < another.cost; }
    void insertEdge(int _dest, int _cost)
    {
        if (dest == -1)
        {
            dest = _dest;
            cost = _cost;
            return;
        }
        Edge *e = this;
        while (e->link != nullptr)
            e = e->link;
        e->link = new Edge(_dest, _cost);
    }
};

int Prim(int **points, int n)
{
    Edge *graph = new Edge[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            int w = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
            graph[i].insertEdge(j, w);
            graph[j].insertEdge(i, w);
        }
    Heap<Edge> MinHeap(n * n);
    bool *visited = new bool[n];
    int *minCost = new int[n];
    int MSTweight = 0;
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
        minCost[i] = INT_MAX;
    }
    MinHeap.insert(Edge(0, 0)); // A dummy edge: from a dummy point to 0, weighing zero
    while (!MinHeap.isEmpty())
    {
        Edge t = MinHeap.delMax();
        Edge *top = &t;
        int u = top->dest;
        if (visited[u])
            continue;
        visited[u] = true;
        MSTweight += top->cost;
        Edge *e = &(graph[u]);
        while (e != nullptr)
        {
            int v = e->dest;
            if (e->cost < minCost[v])
            {
                minCost[v] = e->cost;
                MinHeap.insert(*e);
            }
            e = e->link;
        }
    }
    delete[] minCost; delete[] visited;
    return MSTweight;
}

int main()
{
    int n;
    cin >> n;
    int **points = new int*[n];
    for (int i = 0;i < n; i++)
    {
        points[i] = new int[2];
        int x, y;
        cin >> x >> y;
        points[i][0] = x; points[i][1] = y;
    }
    int MST = Prim(points, n);
    cout << MST << endl;
    for (int i = 0;i < n; i++)
        delete[] points[i];
    delete[] points;
#ifndef OJ
    system("pause");
#endif
    return 0;
}