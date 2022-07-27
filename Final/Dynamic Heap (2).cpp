#include<iostream>
#include<limits.h>
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

class int_greater // 重载int实现小根堆
{
public:
    int elem;
    int_greater(int _elem = 0): elem(_elem) {}
    bool operator>(const int_greater &another) { return elem < another.elem; }
    friend ostream& operator<<(ostream& out, const int_greater &i) { out << i.elem; return out; }
    friend bool operator<(const int x, const int_greater& i) {return x > i.elem; }
};

class int_less
{
public:
    int elem;
    int_less(int _elem = 0): elem(_elem) {}
    bool operator>(const int_less &another) { return elem > another.elem; }
    friend ostream& operator<<(ostream& out, const int_less &i) { out << i.elem; return out; }
    friend bool operator<(const int x, const int_less& i) {return x < i.elem; }
};

int main()
{
    int N, M, temp;
    cin >> M >> N;
    Heap<int_less> MaxHeap(N);  // 大根堆，用于存储较小的 x - ⌈x/M⌉ 个元素
    Heap<int_greater> MinHeap(N); // 小根堆，用于存储最大的⌈x/M⌉个元素
    int *population = new int[N];
    scanf("%d", &temp);
    MinHeap.insert(int_greater(temp));
    cout << MinHeap.getMax().elem << " ";
    for (int i = 1; i < N; i++) {
        scanf("%d", &temp);
        if (temp > MinHeap.getMax().elem) // 若其大于小根堆堆顶，说明其是较大的那部分(⌈x/M⌉个)元素，应该插入小根堆
            MinHeap.insert(int_greater(temp));
        else
            MaxHeap.insert(int_less(temp));
        int pivot = (i + 1 + M - 1) / M; // 这个值就是 ⌈x/M⌉
        if (MinHeap.size() > pivot) { // 动态维护小根堆中元素个数始终为 ⌈x/M⌉
            MaxHeap.insert(int_less(MinHeap.delMax().elem));
        }
        else if (MinHeap.size() < pivot) { // 动态维护小根堆中元素个数始终为 ⌈x/M⌉
            MinHeap.insert(int_greater(MaxHeap.delMax().elem));
        }
        printf("%d ", MinHeap.getMax().elem); // 此时小根堆堆顶一定是最大的`⌈x/M⌉`个元素的最小值
    }
    delete[] population;
#ifndef OJ
    system("pause");
#endif
    return 0;
}