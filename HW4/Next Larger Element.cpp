// Variation of Leetcode 503
// Easy Version: Leetcode 496
#include<iostream>
#include<string>
using namespace std;
#define OJ

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
        if (isEmpty())
            return;
        else 
        {
            T top = Pop();
            PrintInv();
            cout << top;
        }
    }

private:
    T *elem;
    int top;
};

int main()
{
    int num[100000], cnt = 0;
    while (cin >> num[cnt++]);
    cnt--;
    Stack<int> stack(cnt);
    int result[cnt] = {0};
    for (int i = 0; i < cnt; i++)
    {
        if (!i)
            stack.Push(i);
        while (!stack.isEmpty() && num[stack.Peek()] < num[i])
        {
            int pop = stack.Pop();
            result[pop] = i - pop;
        }
        stack.Push(i);
    }
    for (int i = 0; i < cnt; i++)
        cout << result[i] << " ";
#ifndef OJ
    system("pause");
#endif
    return 0;
}