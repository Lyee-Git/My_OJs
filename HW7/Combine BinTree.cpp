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

TreeNode *mergeTrees(TreeNode *a, TreeNode *b)
{
    if (a == nullptr)
        return b;
    if (b == nullptr)
        return a;
    TreeNode *merge = new TreeNode(a->val + b->val);
    merge->left = mergeTrees(a->left, b->left);
    merge->right = mergeTrees(a->right, b->right);
    return merge;
}

void preOrder(TreeNode *root) {
    if (root != nullptr) 
        cout << root->val << " ";
    else
    {
        cout << "-1 ";
        return;
    }
    preOrder(root->left);
    preOrder(root->right);
}

int main()
{
    int Tree_a[20000], Tree_b[20000], size_a = 0, size_b = 0;
    int temp_a, temp_b;
    while (cin >> temp_a)
    {
        Tree_a[size_a++] = temp_a;
        if (cin.get() == '\n')
            break;
    }
    while (cin >> temp_b)
        Tree_b[size_b++] = temp_b;
    TreeNode *a = CreateTree(Tree_a, size_a);
    idx = 0;
    TreeNode *b = CreateTree(Tree_b, size_b);
    TreeNode *merged = mergeTrees(a, b);
    preOrder(merged);
#ifndef OJ
    system("pause");
#endif
    return 0;
}