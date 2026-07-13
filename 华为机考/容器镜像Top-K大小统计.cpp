#include "iostream"
#include "vector"
#include "algorithm"
#include "sstream"
#include "string"

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x),  left(nullptr), right(nullptr) {}
};

TreeNode* build(vector<int>& preorder, vector<int>& inorder) {
    if (inorder.size() == 0) return nullptr;

    int rootValue = preorder[0];
    TreeNode* root = new TreeNode(rootValue);

    int delimiterIndex = 0;
    for (delimiterIndex; delimiterIndex < inorder.size(); delimiterIndex++) {
        if (inorder[delimiterIndex] == rootValue) {
            break;
        }
    }

    vector<int> leftInorder(inorder.begin(), inorder.begin() + delimiterIndex);
    vector<int> rightInorder(inorder.begin() + delimiterIndex + 1, inorder.end());

    preorder.erase(preorder.begin());
    vector<int> leftPreorder(preorder.begin(), preorder.begin() + leftInorder.size());
    vector<int> rightPreorder(preorder.begin() + leftInorder.size(), preorder.end());

    root->left = build(leftPreorder, leftInorder);
    root->right = build(rightPreorder, rightInorder);

    return root;
}

vector<int> record;
void resume_record(TreeNode* root, TreeNode* pre_root, int dir) {
    if (root == nullptr) return;

    if (pre_root != nullptr) {
        root->val += pre_root->val;
    }
    
    if (root->val <= 0) {
        if (pre_root == nullptr) return;
        if (dir == 0) {
            pre_root->left = nullptr;
        } else if (dir == 1) {
            pre_root->right = nullptr;
        }
        if (pre_root->left == nullptr && pre_root->right == nullptr) {
            record.push_back(pre_root->val);
        }
        return;
    }
    
    if (root->left == nullptr && root->right == nullptr) {
        record.push_back(root->val);
    } else {
        resume_record(root->left, root, 0);
        resume_record(root->right, root, 1);
    }
    
    return;
}

int main(void) 
{
    vector<int> preorder;
    vector<int> inorder;
    int K;

    // 数据输入
    string line;
    getline(cin, line);
    stringstream ss(line);
    int temp;
    while (ss >> temp) {
        preorder.push_back(temp);
    }

    line.clear();
    getline(cin, line);
    stringstream ss1(line);
    while (ss1 >> temp) {
        inorder.push_back(temp);
    }

    cin >> K;

    //处理

    // 1.根据前序遍历和中序遍历转换成树
    TreeNode* root = build(preorder, inorder);
    
    // 2.还原节点镜像,并存储根节点
   
    resume_record(root, nullptr, -1);

    // for (auto it : record) {
    //     cout << it << " ";
    // }
    // cout << endl;

    // 3.排序， 输出
    sort(record.begin(), record.end());
    int n = min(K,(int)record.size());
    for (int i = 0; i < n; i++) {
        cout << record[record.size() - n + i];
        if (i != n - 1) {
            cout << " ";
        }
    }

    return 0;
}