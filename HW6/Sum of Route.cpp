#include<iostream>
#include<limits.h>
#include<string>
#define SIZE 16341163
using namespace std;

//#define OJ

// struct prefix_entry
// {
//     int pref, num;
//     prefix_entry(int _pref, int _num = 0): pref(_pref), num(_num) {}
// };

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int prefix_num_mapping[SIZE];

void splitString(string& tree, string* nodes)
{
    int nodes_pos = 0;
    tree.push_back(' ');
    size_t pos = tree.find(' ');
    while (pos != tree.npos)
    {
        string temp = tree.substr(0, pos);
        nodes[nodes_pos++] = temp;
        tree = tree.substr(pos + 1, tree.size());
        pos = tree.find(' ');
    }
}

void buildTree(TreeNode* &root, string* nodes, int N, int i)
{
    if (nodes[i] != "null")
        root->val = stoi(nodes[i]);
    else
    {
        root = nullptr;
        return;
    }
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

void preOrder(TreeNode *root) {
<<<<<<< HEAD
    if(root != nullptr) {
=======
    if(root != NULL) {
>>>>>>> b570a1cacf94d6cfee5245028b7ef4e4e6761927
        cout << root->val << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int DFS(TreeNode *root, int bloodSum, long long cur_val)
{
    if (root == nullptr)
        return 0;
    int result = 0;
    cur_val += root->val;
    if (cur_val - bloodSum >= 0 && prefix_num_mapping[cur_val - bloodSum])
        result += prefix_num_mapping[(cur_val - bloodSum) % SIZE];
    prefix_num_mapping[cur_val % SIZE]++;
    if (root->left != nullptr)
        result += DFS(root->left, bloodSum, cur_val);
    if (root->right != nullptr)
        result += DFS(root->right, bloodSum, cur_val);
    prefix_num_mapping[cur_val % SIZE]--;
    return result;
}

int main()
{
    int bloodSum, N;
    cin >> bloodSum >> N;
    if (!N)
    {
        cout << "0" << endl;
        return 0;
    }
    TreeNode *root = new TreeNode;
    string nodes[N];
    for (int i = 0; i < N; i++)
        cin >> nodes[i];
    buildTree(root, nodes, N, 0);
    //preOrder(root);
    prefix_num_mapping[0] = 1; // if sum of path (from root to leaf) == bloodSum then use prefix_num_mapping[0]
    int res = DFS(root, bloodSum, 0);
    cout << res << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}