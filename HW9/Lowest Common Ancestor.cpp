#include<iostream>
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

int idx = 0, p_val, q_val;

TreeNode *CreateTree(int *a, int size)
{
    if (idx >= size || a[idx] == -1)
    {
        idx++;
        return nullptr;
    }
    TreeNode *root = new TreeNode(a[idx]);
    idx++;
    root->left = CreateTree(a, size);
    root->right = CreateTree(a, size);
    return root;
}

TreeNode* DFS(TreeNode *root, int p, int q){
    if (root == nullptr)
        return nullptr;
    if (root->val == p || root->val == q)
        return root;
    TreeNode *left = DFS(root->left, p, q);
    TreeNode *right = DFS(root->right, p, q);
    if (left && right)
        return root;
    else if (left == nullptr)
        return right;
    else if (right == nullptr)
        return left;
    else // if (left == nullptr && right == nullptr)
        return nullptr;
}

int main()
{
    int *nodes = new int[20000], temp = 0, n = 0;
    while (cin >> temp)
        nodes[n++] = temp;
    p_val = nodes[n - 2];
    q_val = nodes[n - 1];
    n -= 2;
    TreeNode *p, *q;
    TreeNode *root = CreateTree(nodes, n);
    TreeNode *res = DFS(root, p_val, q_val);;
    cout << res->val << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}