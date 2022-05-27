#include<iostream>
#include<cstring> // memset
#include<limits.h>
using namespace std;
//#define OJ

class Bitmap 
{ 
private:
   char* M; // Space for Bitmap
   int N; //capacity = N * sizeof(char) * 8 bits
protected:
   void init (int n) { M = new char[N = ( n + 7 ) / 8]; memset (M, 0, N); }
public:
   Bitmap (int n) { init(n); }
   void set( int k ) { M[k >> 3] |= ( 0x80 >> ( k & 0x07 ) ); }
   void clear( int k ) { M[k >> 3] &= ~ ( 0x80 >> ( k & 0x07 ) ); }
   bool test( int k ) { return M[k >> 3] & ( 0x80 >> ( k & 0x07 ) ); }
};

template<class K, class V>
class Hashtable
{
private:
    pair<K, V> **ht;
    int M; // num of buckets
    int N;  // num of entries
    int hashcode(K k) { return (int)k; }
    Bitmap *Removal; // Marks for removal of each bucket
protected:
    int probeHit(const K& k); // probe for entry bucket we are looking for with key k
    int probeFree(const K& k); // probe for free bucket with key k
    void rehash();
public:
    Hashtable();
    ~Hashtable() { for (int i = 0; i < M; i++) { if (ht[i]) delete[] ht[i]; } delete[] ht; delete Removal; }
    int size() const { return N; }
    bool put(K, V);
    bool remove(K k);
    V* get(K k);
    V& operator[] (K k) { return *(get(k)); } // Only use it when get(k) exists (not nullptr)
};

template<class K, class V> Hashtable<K, V>::Hashtable()
{
    M = 20101;
    N = 0;
    ht = new pair<K, V>*[M];
    Removal = new Bitmap(M);
    memset(ht, 0, sizeof(pair<K, V>*) * M);
}

template<class K, class V> V* Hashtable<K, V>::get(K k)
{
    int target = probeHit(k);
    return ht[target] ? &(ht[target]->second) : nullptr;
}

template<class K, class V> bool Hashtable<K, V>::put(K k, V v)
{
    if (ht[probeHit(k)])
    {
        ht[probeHit(k)]->second = v;
        return false; // Entry with Key k already exists
    }
    int target = probeFree(k);
    ht[target] = new pair<K, V> (k, v);
    N++;
    if (Removal->test(target))
        Removal->clear(target);
    if (N * 2 > M)
        rehash();
    return true;
}

template<class K, class V> bool Hashtable<K, V>::remove(K k)
{
    int target = probeHit(k);
    if (!ht[target])
        return false;
    delete ht[target];
    ht[target] = nullptr;
    Removal->set(target);
    N--;
    return true;
}

template<class K, class V> int Hashtable<K, V>::probeHit(const K& k)
{
    int target = hashcode(k) % M;
    while ((ht[target] && ht[target]->first != k) || (!ht[target] && Removal->test(target)))
        target = (target + 1) % M;
    return target;
}

template<class K, class V> int Hashtable<K, V>::probeFree(const K& k)
{
    int target = hashcode(k) % M;
    while (ht[target])
        target = (target + 1) % M;
    return target;
}

template<class K, class V> void Hashtable<K, V>::rehash()
{
    pair<K, V> **oldht = ht;
    ht = new pair<K, V>*[40213];
    int oldM = M;
    M = 20101; N = 0;
    memset(ht, 0, sizeof(pair<K, V>*) * M);
    for (int i = 0; i < oldM; i++)
        if (oldht[i])
        {
            put(oldht[i]->first, oldht[i]->second);
            //delete oldht[i];
        }
    delete oldht;
    delete Removal;
    Removal = new Bitmap(M);
}

class UnionFindSets
{
private:
    Hashtable<int, int> parent;
    int numCC; 
public:
    UnionFindSets(int _numCC = 0): numCC(_numCC) {}
    int Find(int i) // Collapsing Find
    {
        if (parent.get(i) == nullptr)
        {
            parent.put(i, -1);
            numCC++;
        }
        int root;
        for (root = i; parent.get(root) != nullptr && parent[root] >= 0; root = parent[root]);
        while (i != root)
        {
            int temp = parent[i];
            parent.put(i, root);
            i = temp;
        }
        return root;
    }
    void UnionSet(int a, int b) // Weighted Union
    {
        int rootA = Find(a), rootB = Find(b);
        if (rootA == rootB)
            return;
        int temp = parent[rootA] + parent[rootB];
        //cout << parent[rootA] << " " << parent[rootB] << endl;
        if (parent[rootA] < parent[rootB]) {
            parent[rootB] = rootA;
            parent[rootA] = temp;
        }
        else {
            parent[rootA] = rootB;
            parent[rootB] = temp;
        }
        numCC--;
    }
    int getnumCC() const { return numCC; }
};

int main()
{
    int N;
    cin >> N;
    UnionFindSets UF;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int match;
            cin >> match;
            if (match)
                UF.UnionSet(i, j);
        }
    }
    cout << UF.getnumCC() << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}