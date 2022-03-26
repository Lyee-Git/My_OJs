#include<iostream>
using namespace std;
//#define OJ

class deque
{
public:
    deque(int _size): rear(0), front(0), size(_size) { elem = new int[_size]; }
    ~deque() { delete[] elem; }
    void EnQueueBack(int x) { elem[rear] = x; rear = (rear + 1) % size; }
    int DeQueueHead() 
    {
        int x;
        if (!isEmpty()) { x = elem[front]; front = (front + 1) % size; } 
        return x; 
    }
    int PeekHead() { return elem[front]; }
    void EnQueueHead(int x) { front = (front - 1 + size) % size; elem[front] = x; }
    void DeQueueBack(int &x) { rear = (rear - 1 + size) % size; x = elem[rear]; }
    int PeekBack() {return elem[rear]; }
    bool isEmpty() {return rear == front; }
    bool isFull() {return (rear + 1) % size == front; }
private:
    int *elem;
    int rear, front, size;
};

int main()
{
    int base, cnt, cur = 1, times = 1;
    cin >> base >> cnt; 
    int result[5000000];
    deque a(5000000), b(5000000);
    result[0] = base;
    a.EnQueueBack(2 * base + 1);
    b.EnQueueBack(3 * base + 1);
    while (cur < cnt)
    {
        for (int i = 0; i < 2 * times; i++)
        {
            if (a.PeekHead() < b.PeekHead())
            {
                int temp = a.DeQueueHead();
                if (temp != result[cur - 1])
                    result[cur++] = temp;
                int A = 2 * temp + 1, B = 3 * temp + 1;
                a.EnQueueBack(A);
                b.EnQueueBack(B);
            }
            else
            {
                int temp = b.DeQueueHead();
                if (temp != result[cur - 1])
                    result[cur++] = temp;
                int A = 2 * temp + 1, B = 3 * temp + 1;
                a.EnQueueBack(A);
                b.EnQueueBack(B);
            }
        }
        times *= 2;
    }
    cout << result[cnt - 1] << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}