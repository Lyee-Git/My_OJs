// Leetcode 316
#include<iostream>
#include<string>
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
    string s;
    cin >> s;
    Stack<char> stack(s.length());
    int frequence[26] = {0}, presence[26] = {0};
    for (auto it : s)
        frequence[it - 'a']++;
    int len = s.length();
    for (int i = 0; i < len; i++)
    {
        frequence[s[i] - 'a']--;
        if (!i)
        {
            stack.Push(s[i]);
            presence[s[i] - 'a'] = 1;
            continue;
        }
        if (!presence[s[i] - 'a'])
        {
            while (stack.Peek() > s[i] && frequence[stack.Peek() - 'a'])
            {
                presence[stack.Peek() - 'a'] = 0;
                stack.Pop();
            }
            stack.Push(s[i]);
            presence[s[i] - 'a'] = 1;
        }
    }
    stack.PrintInv();
#ifndef OJ
    system("pause");
#endif
    return 0;
}