#include<iostream>
#include<limits.h>
using namespace std;
//#define OJ

template<class T>
class Stack
{
public:
    Stack(int size): top(-1) {elem = new T[size]; }
    ~Stack() {delete[] elem;}
    void Push(const T& x) {elem[++top] = x; }
    T Pop() {T x = elem[top--]; return x;}
    T Peek() {T x = elem[top]; return x;}
    bool isEmpty()const {return top == - 1; }
    int getSize()const {return top + 1; }
    void PrintInv()
    {
        if (isEmpty()) return;
        else { T top = Pop(); PrintInv(); cout << top << " "; }
    }

private:
    T *elem;
    int top;
};

int main()
{
    int n;
    cin >> n;
    int elem[n];
    for (int i = 0; i < n; i++)
        cin >> elem[i];
    Stack<int> sta(n);
    sta.Push(elem[0]);
    for (int i = 1; i < n; i++)
    {
        if (elem[i] < 0 && !sta.isEmpty() && sta.Peek() > 0)
        {    
            while (!sta.isEmpty() && sta.Peek() > 0 && sta.Peek() < -elem[i])
                sta.Pop();
            if (!sta.isEmpty() && sta.Peek() == -elem[i])
                sta.Pop();
            else if (sta.isEmpty() || sta.Peek() < 0)
                sta.Push(elem[i]);
        }
        else
            sta.Push(elem[i]);
    }
    sta.PrintInv();
#ifndef OJ
    system("pause");
#endif
    return 0;
}