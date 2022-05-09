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

TreeNode *CreateTree(int *a, int size, TreeNode *&p, TreeNode *&q)
{
    if (idx >= size || a[idx] == -1)
    {
        idx++;
        return nullptr;
    }
    TreeNode *root = new TreeNode(a[idx]);
    if (a[idx] == p_val)
        p = root;
    else if (a[idx] == q_val)
        q = root;
    idx++;
    root->left = CreateTree(a, size, p, q);
    root->right = CreateTree(a, size, p, q);
    return root;
}

bool DFS(TreeNode *root, TreeNode* p, TreeNode* q, TreeNode *& res){
    if (root == nullptr)
        return false;
    bool inLC = DFS(root->left, p, q, res); // p or q in left subtree of root
    bool inRC = DFS(root->right, p, q, res);
    bool Equal = root == p || root == q;
    if (Equal && (inLC || inRC) || inLC && inRC)
        res = root;
    return Equal || inRC || inLC;
}

int main()
{
    int *nodes = new int[10002], temp = 0, n = 0;
    while (cin >> temp)
        nodes[n++] = temp;
    p_val = nodes[n - 2];
    q_val = nodes[n - 1];
    n -= 2;
    TreeNode *p, *q;
    TreeNode *root = CreateTree(nodes, n, p, q);
    TreeNode *res;
    DFS(root, p, q, res);
    cout << res->val << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}