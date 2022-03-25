#include<iostream>
#include<vector>
#include<cstdio>
#define OJ
using namespace std;

template<class T>
class Heap
{
public:
    Heap(): HeapSize(0) {};
    void insert(T);
    void insert(int);
    T delMax();
    T getMax();
    bool isEmpty();
    int size();
private:
    vector<T> elem;
    int HeapSize;
    void percolateDown(int i);
    void percolateUp(int i);
    //void Heapify(int n);
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

template<class T> void Heap<T>::insert(T e)
{
    elem.emplace_back(e);
    percolateUp(HeapSize++);
}

template<class T> void Heap<T>::insert(int e)
{
    insert(T(e));
}


template<class T> T Heap<T>::delMax()
{
    T max = elem[0];
    elem[0] = elem[--HeapSize];
    elem.pop_back();
    percolateDown(0);
    return max;
}

template<class T> T Heap<T>::getMax()
{
    return elem[0];
}

template<class T> bool Heap<T>::isEmpty()
{
    return HeapSize == 0;
}

template<class T> int Heap<T>::size()
{
    return HeapSize;
}

class int_less
{
public:
    int elem;
    int_less(int _elem): elem(_elem) {}
    bool operator>(const int_less &another) { return elem < another.elem; }
    friend ostream& operator<<(ostream& out, const int_less &i) { out << i.elem; return out; }
    friend bool operator<(const int x, const int_less& i) {return x < i.elem; }
};

class int_greater
{
public:
    int elem;
    int_greater(int _elem): elem(_elem) {}
    bool operator>(const int_greater &another) { return elem > another.elem; }
    friend ostream& operator<<(ostream& out, const int_greater &i) { out << i.elem; return out; }
    friend bool operator<(const int x, const int_greater& i) {return x < i.elem; }
};

int main()
{
    int num = 0;
    Heap<int_less> MinHeap;
    Heap<int_greater> MaxHeap;
    while (scanf("%d", &num) != EOF)
    {
        if (MaxHeap.isEmpty())
        {
            MaxHeap.insert(num);
            printf("%d ", num);
            continue;
        }
        num < MaxHeap.getMax() ? MaxHeap.insert(num) : MinHeap.insert(num);
        if (MaxHeap.size() > MinHeap.size() + 1)
        {
            int temp = MaxHeap.delMax().elem;
            MinHeap.insert(temp);
        }
        else if (MinHeap.size() > MaxHeap.size() + 1)
        {
            int temp  = MinHeap.delMax().elem;
            MaxHeap.insert(temp);
        }
        if (MaxHeap.size() < MinHeap.size())
            printf("%d ", MinHeap.getMax().elem);
        else
            printf("%d ", MaxHeap.getMax().elem);
    }
#ifndef OJ
    system("pause");
#endif
        return 0;
}
