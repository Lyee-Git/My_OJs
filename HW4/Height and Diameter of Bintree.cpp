#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
//#define OJ
using namespace std;
int diameterNodes = 1;
vector<int> preorder;
vector<int> inorder;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int depth(TreeNode *root)
{
    if (root == nullptr)
        return 0;
    int left = depth(root->left);
    int right = depth(root->right);
    diameterNodes = max(diameterNodes, left + right + 1);
    return max(left, right) + 1;
}

TreeNode* Create(int L_preorder, int R_preorder, int L_inorder, int R_inorder, int *val2idx) // Hash from value of node to index of inorder array
{
    if (L_preorder > R_preorder)
        return nullptr;
    TreeNode *root = new TreeNode(preorder[L_preorder]);
    int root_inorder = val2idx[preorder[L_preorder]];
    int size_leftSubTree = root_inorder - L_inorder;
    root->left = Create(L_preorder + 1, L_preorder + size_leftSubTree, L_inorder, root_inorder - 1, val2idx);
    root->right = Create(L_preorder + size_leftSubTree + 1, R_preorder, root_inorder + 1, R_inorder, val2idx);
    return root;
}

int main()
{
    int n, temp;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        preorder.emplace_back(temp);
    }
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        inorder.emplace_back(temp);
    }
    int val2idx_inorder[n];
    for (int i = 0; i < n; i++)
        val2idx_inorder[inorder[i]] = i;
    TreeNode *root = Create(0, preorder.size() - 1, 0, inorder.size() - 1, val2idx_inorder);
    int _depth = depth(root);
    cout << "I have read the rules about plagiarism punishment" << endl;
    cout << _depth - 1 << endl;
    cout << diameterNodes - 1 << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}