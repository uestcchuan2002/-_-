#include "iostream"
#include "vector"
#include "string"
#include "sstream"

using namespace std;

struct TreeRoot
{
    int val;
    TreeRoot *left;
    TreeRoot *right;
    TreeRoot(int x) :val(x), left(nullptr), right(nullptr) {}
};

TreeRoot* buildTree(vector<int> &preorder, vector<int> &inorder) {
    if (preorder.size() == 0) {
        return nullptr;
    }
    // 构建根节点
    int root_val = preorder[0];
    TreeRoot* root = new TreeRoot(root_val);
    // 找到根节点在中序遍历中的下标
    int mid_index = 0;
    for (; mid_index < inorder.size(); mid_index++) {
        if (root_val == inorder[mid_index]) {
            break;
        }
    }
    // 根据下标划分中序遍历
    vector<int> inorder_left(inorder.begin(), inorder.begin() + mid_index);
    vector<int> inorder_right(inorder.begin() + mid_index + 1, inorder.end());

    vector<int> temp_preorder = preorder;
    temp_preorder.erase(temp_preorder.begin());
    // 根据中序遍历的数据数量划分
    vector<int> preorder_left(temp_preorder.begin(), temp_preorder.begin() + inorder_left.size());
    vector<int> preorder_right(temp_preorder.begin() + inorder_left.size(), temp_preorder.end());
    root->left = buildTree(preorder_left, inorder_left);
    root->right = buildTree(preorder_right, inorder_right);
    return root;
}

static int result = 0;
static int nums = 0;
void dfs(TreeRoot* root, TreeRoot* pre_root) {
    if (root == nullptr) {
        return;
    }
    if (pre_root != nullptr) {
        root->val += pre_root->val;
    }
    result += root->val;
    nums++;
    if (root->val <= 0) {
        root->left = nullptr;
        root->right = nullptr;
        result -= root->val;
        nums--;
    }


    dfs(root->left, root);
    dfs(root->right, root);
    
    return;
}

int main() 
{
    vector<int> preorder;
    vector<int> inorder;
    string line;
    
    getline(cin, line);
    int x;
    stringstream ss_pre(line);
    while (ss_pre >> x) {
        preorder.push_back(x);
    }
    
    getline(cin, line);
    stringstream ss_in(line);
    while (ss_in >> x) {
        inorder.push_back(x);
    }

    // 构建树
    TreeRoot* root = buildTree(preorder, inorder);
    // dfs
    dfs(root, nullptr);
    // 输出
    if (nums == 0) {
        cout << 0 << endl;
    } else {
        cout << (int)(result / nums) << endl;
    }

    return 0;
}