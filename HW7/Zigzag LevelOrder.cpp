#include<iostream>
#include<string>
using namespace std;
//#define OJ

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

template<class T>
class deque
{
public:
    deque(int _capacity): rear(0), front(0), _size(0), capacity(_capacity) { elem = new T[_capacity]; }
    ~deque() { delete[] elem; }
    void Push_Back(T &x) { elem[rear] = x; rear = (rear + 1) % capacity; _size++; }
    T Pop_Front() 
    {
        T x;
        if (!isEmpty()) { x = elem[front]; front = (front + 1) % capacity; } 
        _size--;
        return x; 
    }
    T Front() { return elem[front]; }
    void Push_Front(T &x) { front = (front - 1 + capacity) % capacity; elem[front] = x; _size++; }
    void Pop_Back(T &x) { rear = (rear - 1 + capacity) % capacity; x = elem[rear]; _size--;}
    T Back() {return elem[rear]; }
    int size() { return _size; }
    bool isEmpty() {return rear == front; }
    bool isFull() {return (rear + 1) % capacity == front; }
private:
    T *elem;
    int rear, front, _size, capacity;
};

int idx = 0;

TreeNode *CreateTree(int *a, int size)
{
    if (idx >= size || a[idx] == -1)
    {
        idx++;
        return nullptr;
    }
    TreeNode *root = new TreeNode(a[idx++]);
    root->left = CreateTree(a, size);
    root->right = CreateTree(a, size);
    return root;
}

int main()
{
    int N;
    cin >> N;
    int a[N];
    for (int i = 0; i < N; i++)
        cin >> a[i];
    TreeNode *root = CreateTree(a, N);
    deque<TreeNode*> que(N);
    que.Push_Back(root);
    bool inverse = false;
    while (!que.isEmpty())
    {
        int size = que.size();
        deque<int> level(N);
        while (size--)
        {
            TreeNode *cur = que.Pop_Front();
            if (!inverse)
                level.Push_Back(cur->val);
            else
                level.Push_Front(cur->val);
            if (cur->left)
                que.Push_Back(cur->left);
            if (cur->right)
                que.Push_Back(cur->right);
        }
        while (!level.isEmpty())
            cout << level.Pop_Front() << " ";
        cout << endl;
        inverse = !inverse;
    }
#ifndef OJ
    system("pause");
#endif
    return 0;
}