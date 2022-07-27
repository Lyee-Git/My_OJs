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
    if (lc < HeapSize && elem[lc] > elem[i])
        j = lc;
    if (rc < HeapSize && elem[rc] > elem[lc] && elem[rc] > elem[i])
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
        if (elem[i] > elem[j])
        {
            swap(elem[i], elem[j]);
            i = j;
        }
        else
            break;
    }
}

template<class T> void Heap<T>::Heapify() // 利用已有数组直接建堆
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

int main()
{
    int M, N, result;
    cin >> M >> N;
    int *population = new int[N];
    for (int i = 0; i < N; i++)
        cin >> population[i]; 
    Heap<int> cities(population, N); // 城市人口数据建堆
    for (int i = 0; i < M; i++)
        result = cities.delMax(); // 不断取最大堆堆顶元素，取M次即可找到最大的M个数中最小的
    cout << result << endl;
    delete[] population;
#ifndef OJ
    system("pause");
#endif
    return 0;
}