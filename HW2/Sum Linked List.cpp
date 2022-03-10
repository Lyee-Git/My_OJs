#include<iostream>
#define OJ
using namespace std;

class node
{
public:
    int num;
    node *succ;
    node(int _num = -1, node* _succ = nullptr):num(_num), succ(_succ) {};
};

node *Add(node *a, node *b)
{
    bool CF = false;
    node *result = new node();
    node *ret = result;
    while (a || b || CF)
    {
        int sum = CF;
        if (a) sum += a->num;
        if (b) sum += b->num;
        CF = sum >= 10;
        result->succ = new node(CF ? sum - 10 : sum);
        result = result->succ;
        if (a) a = a->succ;
        if (b) b = b->succ;
    }
    return ret;  
}

int main()
{
    node *temp = nullptr;
    int num = 0, tmp = 0;
    node *a = new node;
    temp = a;
    while (cin >> tmp)
    {
        if (tmp == -1)
            break;
        temp->succ = new node(tmp);
        temp = temp->succ;
    }
    node *b = new node;
    temp = b;
    while (cin >> tmp)
    {
        if (tmp == -1)
            break;
        temp->succ = new node(tmp);
        temp = temp->succ;
    }
    node *result = Add(a->succ, b->succ);
    while ((result = result->succ) != nullptr)
        cout << result->num << " ";
#ifndef OJ
    system("pause");
#endif
    return 0;
}