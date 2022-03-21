//Leetcode 950
#include<iostream>
using namespace std;
#define OJ

class deque
{
public:
    deque(int _size): rear(0), front(0), size(_size) { elem = new int[_size]; }
    ~deque() { delete[] elem; }
    void EnQueueBack(int &x) { elem[rear] = x; rear = (rear + 1) % size; }
    bool DeQueueHead(int &x) 
    {
        if (!isEmpty()) { x = elem[front]; front = (front + 1) % size; } 
        return true; 
    }
    int PeekHead() { return elem[front]; }
    void EnQueueHead(int &x) { front = (front - 1 + size) % size; elem[front] = x; }
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
    int n_card;
    cin >> n_card;
    int Cards[n_card], temp = 0;
    deque cards_shuffle(n_card + 1);
    for (int i = n_card - 1; i >= 0; i--)
        cin >> Cards[i];
    for (int i = 0; i < n_card; i++)
    {
        if (i)
        {    
            cards_shuffle.DeQueueBack(temp);
            cards_shuffle.EnQueueHead(temp);
        }
        cards_shuffle.EnQueueHead(Cards[i]);
    }
    while (!cards_shuffle.isEmpty())
    {
        cards_shuffle.DeQueueHead(temp);
        cout << temp << " ";
    }
#ifndef OJ
    system("pause");
#endif
    return 0;
}