#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdio>
using namespace std;
#define OJ

// The Part of Heap Structure
template<class T>
class Heap
{
public:
    Heap(): HeapSize(0) {};
    void insert(T);
    void insert(int);
    T delMax();
    T getMax();
    void Popk(int k);
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

template<class T> void Heap<T>::Popk(int k)
{
    if (!k)
        return;
    T top = delMax();
    Popk(--k);
    cout << top << " ";
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

// The Part of Median of Median Algorithm
int SELECT_WLINEAR(int *elem, int lo, int hi, int k);

int median(int *elem, int lo, int hi)
{
    sort(elem + lo, elem + hi + 1);
    return elem[(lo + hi) >> 1];
}

int MedianOfMedian(int *elem, int lo, int hi)
{
    int len = (hi - lo + 4) / 5;
    int medians[len];
    for (int i = 0; i < len; i++)
        medians[i] = median(elem, lo + i * 5, lo + i * 5 + 4 < hi ? lo + i * 5 + 4 : hi);
    return SELECT_WLINEAR(medians, 0, len - 1, len >> 1); // Use len >> 1 instead of (len - 1) >> 1 to avoid segmentation fault
}

// Get Range[2]: Elements within [Range[0], Range[1]] equal pivot
void Partition(int *elem, int *range, int lo, int hi, int pivot) 
{
    int left = lo - 1, offset = 0, cur; // Target: Any element within [left + 1, left + offset] == pivot
    for (cur = lo; cur <= hi; cur++)
    {
        if (elem[cur] == pivot)
        {
            offset++;
            int temp = elem[cur];
            elem[cur] = elem[left + offset];
            elem[left + offset] = temp;
        }
        else if (elem[cur] < pivot)
        {
            left++;
            int temp = elem[left];
            elem[left] = elem[cur];
            if (!offset)
                elem[cur] = temp;
            else
            {
                elem[cur] = elem[left + offset];
                elem[left + offset] = temp;
            }
        }
    }
    range[0] = left + 1;
    range[1] = left + offset;
}

int SELECT_WLINEAR(int *elem, int lo, int hi, int k)
{
    if (lo == hi)
        return elem[lo];
    int pivot = MedianOfMedian(elem, lo, hi);
    int range[2];
    Partition(elem, range, lo, hi, pivot);
    if (k >= range[0] && k <= range[1])
        return elem[k];
    else if (k < range[0])
        return SELECT_WLINEAR(elem, lo, range[0] - 1, k);
    else
        return SELECT_WLINEAR(elem, range[1] + 1, hi, k);
}

int main()
{
    int k, n;
    scanf("%d %d", &k, &n);
    int *elem = new int[n];
    for (int i = 0; i < n; i++)
       scanf("%d", &elem[i]);
    int mid = (n - 1) >> 1;
    int median = SELECT_WLINEAR(elem, 0, n - 1, mid);
    Heap<int_greater> MaxHeap;
    Heap<int_less> MinHeap;
    for (int i = mid - 1; i >= 0; i--)
        MaxHeap.insert(elem[i]);
    MaxHeap.Popk(k);
    cout << median << " ";
    for (int i = mid + 1; i < n; i++)
        MinHeap.insert(elem[i]);
    for (int i = 0; i < k; i++)
        cout << MinHeap.delMax() << " ";
    delete[] elem;
#ifndef OJ
    system("pause");
#endif
    return 0;
}