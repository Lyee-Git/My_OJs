#include<iostream>
#define OJ
using namespace std;

class Node
{
public:
    int num;
    Node *pred, *succ;
    Node(int _num, Node *l = nullptr, Node *r = nullptr): num(_num), pred(l), succ(r) {}
    ~Node() {};
};

class List
{
private:
    Node *first;
public:
    List(int _num)
    {
        first = new Node(_num);
        first->pred = first->succ = first;
    }
    ~List() {};

    Node *Locate(int i, int d = 1) // for d == 0 : pred direction ; d == 1 : succ direction
    {
        if (first->succ == first || i == 1)
            return first;
        Node *current = nullptr;
        current = d == 0 ? first->pred : first->succ;
        for (int j = 1; j < i - 1; j++)
        {
            // if (current == first)
            //     break;
            // else 
            if (d == 0)
                current = current->pred;
            else
                current = current->succ;
        }
        // If aiming to locate rigorously at n th node after first node, then:
        // if (current == first)
        //     current = nullptr;
        // But for Joseph problem, we only need a node counter
        return current;
    }

    Node* &getFirst()
    {
        return first;
    }

    void setFirst(int i)
    {
        first = Locate(i);
        return;
    }

    void setFirst(Node* &_first)
    {
        first = _first;
        return;
    }

    void Insert(int i, const int& x)
    {
        Node *current = Locate(i);
        Node *newNode = new Node(x);
        newNode->succ = current->succ;
        current->succ = newNode;
        newNode->succ->pred = newNode;
        newNode->pred = current;
        return;
    }

    void Remove(int i, int d, Node* &res)
    {
        Node *current = Locate(i, d);
        current->pred->succ = current->succ;
        current->succ->pred = current->pred;
        res = d == 0 ? current->pred : current->succ;
        cout << current->num << " ";
        delete current;
        return;
    }
};

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    List Joseph_List(1);
    for (int i = 2; i <= n; i++)
        Joseph_List.Insert(i - 1, i);
    Joseph_List.setFirst(k);
    Node *res = nullptr;
    for (int j = 0; j < n; j++)
    {
        Joseph_List.Remove(m, 1, res);
        Joseph_List.setFirst(res);
        //cout << Joseph_List.getFirst()->num << endl;
    }
    cout << endl;

    List Joseph_List_Reverse(1);
    for (int i = 2; i <= n; i++)
        Joseph_List_Reverse.Insert(i - 1, i);
    Joseph_List_Reverse.setFirst(k);
    res = nullptr;
    for (int j = 0; j < n; j++)
    {
        Joseph_List_Reverse.Remove(m, 0, res);
        Joseph_List_Reverse.setFirst(res);
    }
    #ifndef OJ
        system("pause");
    #endif
    return 0;
}