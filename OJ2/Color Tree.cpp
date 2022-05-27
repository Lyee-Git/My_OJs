#include<iostream>
#include<vector>
#include<limits.h>
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

void buildTree(TreeNode* &root, int* nodes, int N, int i)
{
    root->val = nodes[i];
    if (2 * i + 1 < N)
    {
        root->left = new TreeNode;
        buildTree(root->left, nodes, N, 2 * i + 1);
    }
    if (2 * i + 2 < N)
    {
        root->right = new TreeNode;
        buildTree(root->right, nodes, N, 2 * i + 2);
    }    
}

int DFS(TreeNode *root, int &X_LeftSubTree, int &X_RightSubTree, int X)
{
    if (root == nullptr)
        return 0;
    int left = DFS(root->left, X_LeftSubTree, X_RightSubTree, X);
    int right = DFS(root->right, X_LeftSubTree, X_RightSubTree, X);
    if (root->val == X)
    {
        X_LeftSubTree = left;
        X_RightSubTree = right;
    }
    return left + right + 1;
}

int main()
{
    int X, N;
    cin >> X >> N;
    int *nodes = new int[N];
    for (int i = 0; i < N; i++)
        cin >> nodes[i];
    TreeNode *root = new TreeNode;
    buildTree(root, nodes, N, 0);
    int X_LeftSubTree, X_RightSubTree;
    DFS(root, X_LeftSubTree, X_RightSubTree, X);
    if (X_LeftSubTree > N / 2 || X_RightSubTree > N / 2 || N - 1 - X_LeftSubTree - X_RightSubTree > N / 2)
        cout << "true" << endl;
    else
        cout << "false" << endl;
    delete[] nodes;
#ifndef OJ
    system("pause");
#endif
    return 0;
}