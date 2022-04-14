#include<iostream>
#include<limits.h>
#include<string>
//#define OJ
using namespace std;

struct TreeNode {
    int val;
    int depth;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr), depth(0) {}
    TreeNode(int x, int _depth = 0) : val(x), depth(_depth), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), depth(0), left(left), right(right) {}
};

template<class T>
class deque
{
public:
    deque(int _size): rear(0), front(0), size(_size) { elem = new T[_size]; }
    ~deque() { delete[] elem; }
    void Push_Back(T &x) { elem[rear] = x; rear = (rear + 1) % size; }
    T Pop_Front() 
    {
        T x;
        if (!isEmpty()) { x = elem[front]; front = (front + 1) % size; } 
        return x; 
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

int max_dep = -1;
TreeNode *max_tree = nullptr;

void buildTree(TreeNode* &root, int* nodes, int lo, int hi, int depth)
{
    int max = INT_MIN, max_pos = 0;
    if (lo >= hi)
    {
        if (lo == hi)
        {
            root->val = nodes[lo];
            root->depth = depth;
            if (depth >= max_dep)
            {   
                max_dep = depth;
                max_tree = root;
            }
        }
        else
            root = nullptr;
        return;
    }
    for (int i = lo; i <= hi; i++)
        if (nodes[i] > max)
        {
            max = nodes[i];
            max_pos = i;
        }
    root->val = max;
    root->depth = depth;
    if (depth >= max_dep)
    {
        max_dep = depth;
        max_tree = root;
    }
    root->left = new TreeNode;
    buildTree(root->left, nodes, lo, max_pos - 1, depth + 1);
    root->right = new TreeNode;
    buildTree(root->right, nodes, max_pos + 1, hi, depth + 1);
}

void levelTraverse(TreeNode *root, int N) 
{
    deque<TreeNode*> queue(N * 3);
    queue.Push_Back(root);
    while (!queue.isEmpty())
    {
        TreeNode *temp = queue.Pop_Front();
        if (temp == nullptr)
        {
            cout << "-1 ";
            continue;
        }
        cout << temp->val << " ";
        queue.Push_Back(temp->left);
        queue.Push_Back(temp->right);
        if (temp == max_tree)
            break;
    }
}

int main()
{
    int N;
    cin >> N;
    int nodes[N];
    for (int i = 0; i < N; i++)
        cin >> nodes[i];
    TreeNode *root = new TreeNode;
    buildTree(root, nodes, 0, N - 1, 0);
    levelTraverse(root, N);
#ifndef OJ
    system("pause");
#endif
    return 0;
}