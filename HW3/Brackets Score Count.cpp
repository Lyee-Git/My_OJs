// Leetcode 856
// O(N) Both Time & Space
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
    bool Pop(T& x) {x = elem[top--]; return true;}
    bool Peek(T& x) {x = elem[top]; return true;}
    bool isEmpty()const {return top == - 1; }
    int getSize()const {return top + 1; }

private:
    T *elem;
    int top;
};

int main()
{
    string expr;
    int len, Score = 0, temp = 0;
    cin >> len >> expr;
    Stack<int> scores(len);
    for (int i = 0; i < len; i++)
    {
        if (expr[i] == '(')
            scores.Push(0);
        else
        {
            int a = 0, b = 0;
            scores.Pop(a);
            if (!scores.isEmpty())
                scores.Pop(b);
            scores.Push(!a ? 1 + b : a * 2 + b);
        }
    }
    while (!scores.isEmpty() && scores.Pop(temp))
        Score += temp;
    cout << Score << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}