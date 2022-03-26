#include<iostream>
using namespace std;
//#define OJ

template<class T>
class deque
{
public:
    deque(int _size): rear(0), front(0), size(_size) { elem = new T[_size]; }
    ~deque() { delete[] elem; }
    void Push_Back(T &x) { elem[rear] = x; rear = (rear + 1) % size; }
    bool Pop_Front(T &x) 
    {
        if (!isEmpty()) { x = elem[front]; front = (front + 1) % size; } 
        return true; 
    }
    T Front() { return elem[front]; }
    void Push_Front(T &x) { front = (front - 1 + size) % size; elem[front] = x; }
    void Pop_Back(T &x) { rear = (rear - 1 + size) % size; x = elem[rear]; }
    T Back() {return elem[rear]; }
    bool isEmpty() {return rear == front; }
    bool isFull() {return (rear + 1) % size == front; }
private:
    T *elem;
    int rear, front, size;
};

class Cell
{
public:
    int row, col, dist;
    Cell(int _row = 0, int _col = 0, int _dist = 0): row(_row), col(_col), dist(_dist) {}
    // Cell(const Cell& ) = default;
    // Cell(Cell&& ) = default;
    bool operator==(const Cell& another) {return row == another.row && col == another.col; }
    Cell operator+(const Cell& another) {return Cell(row + another.row, col + another.col, dist + another.dist); }
};

Cell ESWN[4] = {Cell(1, 0, 1), Cell(0, 1, 1), Cell(-1, 0, 1), Cell(0, -1, 1)}; // Four Orientations
Cell Portal[10];
int Portal_pos = 0, rows, cols;
Cell Start, End;
char ** labyrinth;

void BFS()
{
    deque<Cell> queue(rows * cols + 1);
    queue.Push_Back(Start);
    while (!queue.isEmpty())
    {
        Cell cur;
        queue.Pop_Front(cur);
        if (cur == End)
        { cout << cur.dist << endl; return; } 
        for (int i = 0; i < 4; i++)
        {
            Cell next = cur + ESWN[i];
            if (next.row < rows && next.col < cols && next.row >= 0 && next.col >= 0)
            {
                if (labyrinth[next.row][next.col] == '0' || labyrinth[next.row][next.col] == 'E')
                {
                    queue.Push_Back(next);
                    labyrinth[next.row][next.col] = '1';
                }
                else if (labyrinth[next.row][next.col] == '*')
                {
                    queue.Push_Back(next);
                    labyrinth[next.row][next.col] = '1';
                    for (int j = 0; j < Portal_pos; j++)
                        if (labyrinth[Portal[j].row][Portal[j].col] != '1')  // Whenever there is an available Portal, push it into queue
                        {
                            labyrinth[Portal[j].row][Portal[j].col] = '1';
                            Portal[j].dist = next.dist + 1;
                            queue.Push_Back(Portal[j]);
                        }
                }
            }
        }
    }
    cout << "-1" << endl;
}

int main()
{
    cin >> rows >> cols;
    labyrinth = new char*[rows];
    for (int i = 0; i < rows; i++)
    {
        labyrinth[i] = new char[cols];
        for (int j = 0; j < cols; j++)
        {
            cin >> labyrinth[i][j];
            switch (labyrinth[i][j])
            {
            case 'S':
                Start = Cell(i, j, 0); break;
            case 'E':
                End = Cell(i, j, 0); break;
            case '*':
                Portal[Portal_pos++] = Cell(i, j, 0);
            default: break;
            }
        }
    }
    BFS();
    for(int i = 0; i < rows; i++)
        delete[] labyrinth[i];
    delete[] labyrinth;
#ifndef OJ
    system("pause");
#endif
    return 0;
}