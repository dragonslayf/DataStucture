#include <iostream>
#include <fstream>
#include <string>
#include<stack>
#include<queue>
using namespace std;

// 二叉树节点的数据结构
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    bool flag;
    int LTag, RTag;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr), flag(true), LTag(0), RTag(0) {}
};

void deleteTree(TreeNode* root);
// 插入节点到二叉树, 二叉搜索树
TreeNode* insert(TreeNode* root, int data) {
    if (!root) {
        return new TreeNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

// 从文件中读取数据并构建二叉树
TreeNode* buildTreeFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return nullptr;
    }

    TreeNode* root = nullptr;
    int value;
    while (file >> value) {
        root = insert(root, value);
    }

    file.close();
    return root;
}

// 三种递归遍历算法，用于对非递归算法的验证。
void inorderTraversal(TreeNode* root) {
    if (root) {
        inorderTraversal(root->left);
        cout << root->data << " ";
        inorderTraversal(root->right);
    }
}

void preorderTraversal(TreeNode* root){
    if(root){
        cout << root->data << " ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(TreeNode* root){
    if(root){
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        cout << root->data << " ";
    }
}
//中序遍历的非递归写法
void inorder_iterative(TreeNode* root){
    stack<TreeNode* > st;
    stack<int> statuses;   //用于存放每个节点的状态，若为1代表右子树还没有遍历，此时就应该打印本节点的data后遍历右子树，否则代表右子树已经遍历，节点被pop。
    st.push(root);
    statuses.push(1);
    while(!st.empty()){
        TreeNode* t = st.top();
        int status = statuses.top();
        if(status == 1){ // 节点一开始都是状态为1
            statuses.pop();
            statuses.push(2);
            if(t->left){
                st.push(t->left);
                statuses.push(1);
            }
        }
        else{
            cout << t->data << " ";
            statuses.pop();
            TreeNode* tmp = t->right;
            st.pop();
            if(tmp){
                statuses.push(1);
                st.push(tmp);
            }
        }
    }
}

//中序遍历非递归算法的改进（书上版本）
void inorder_iterative_2th(TreeNode* root){//改进后的中序遍历，空间复杂度变小了
    stack<TreeNode *> st;
    TreeNode *q;
    while(root || !st.empty()){
        if(root){
            st.push(root);
            root = root->left;
        }
        else{
            q = st.top();
            st.pop();
            cout << q->data << " ";
            root = q->right;
        }
    }
}

//后序遍历的非递归写法（前序遍历非递归和中序遍历非递归写法类似，只需改变打印节点data值的顺序就行）
void postorder_iterative(TreeNode* root){ // 后序遍历相对前序遍历和中序遍历，难点在于难以确定何时该打印节点的data值，一般来说，节点有三个状态，分别是未遍历左子树，此时进入第一个if
//进行左子树的遍历，未遍历右子树和左右子树均遍历完。其中，后两个状态只能借助一个辅助标记位来区分。每个node节点增加flag标记，flag为真时，代表为2状态，否则为3状态。
    stack<TreeNode *> st;
    TreeNode *q;
    while(root || !st.empty()){
        if(root){
            st.push(root);
            root = root->left;
        }
        else{
            q = st.top();
            if(q->flag){
                q->flag = false;
                //开始遍历右子树
                root = q->right;
            }
            else{
                cout << q->data << " ";
                st.pop();
            }
        }
    } 
}

int depth(TreeNode *root);

int nodeCount(TreeNode *root);
int nodeCount_degree0(TreeNode *root);
int nodeCount_degree1(TreeNode *root);
int nodeCount_degree2(TreeNode *root);

int main() {
    string filename = "input_tree.txt"; // 替换成您的文件名
    TreeNode* root = buildTreeFromFile(filename);

    cout << "Postorder traversal of the binary tree: ";
    postorderTraversal(root);
    cout << endl;
    cout << "Postorder_Non_recursive of the tree: " << endl;
    postorder_iterative(root);
    cout << endl;
    cout << "度为2的节点个数为: " << nodeCount_degree2(root) << endl;
    cout << "度为1的节点个数为: " << nodeCount_degree1(root) << endl;
    cout << "度为0的节点个数为: " << nodeCount_degree0(root) << endl;
    cout << "总节点个数为: " << nodeCount(root) << endl;
    cout << "树的深度为: " << depth(root) << endl;
    // 清理内存（可选）
    // TODO: 编写释放内存的函数
    deleteTree(root);
    return 0;
}

void deleteTree(TreeNode* root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

int depth(TreeNode *root){//计算树的深度
    if(!root) return 0;
    int m = depth(root->left);
    int n = depth(root->right);
    return max(m, n) + 1;
}

int nodeCount(TreeNode *root){
    if(!root) return 0;
    return nodeCount(root->left) + nodeCount(root->right) + 1;
}

int nodeCount_degree0(TreeNode *root){
    if(!root) return 0;
    TreeNode *l, *r;
    l = root->left;
    r = root->right;
    if(!l && !r){
        return nodeCount_degree0(l) + nodeCount_degree0(r) + 1;
    }
    return nodeCount_degree0(l) + nodeCount_degree0(r);

}

int nodeCount_degree1(TreeNode *root){
    if(!root) return 0;
    TreeNode *l, *r;
    l = root->left;
    r = root->right;
    if((l && !r) || (!l && r)){
        return nodeCount_degree1(l) + nodeCount_degree1(r) + 1;
    }
    return nodeCount_degree1(l) + nodeCount_degree1(r);
}

int nodeCount_degree2(TreeNode *root){
    if(!root) return 0;
    TreeNode *l, *r;
    l = root->left;
    r = root->right;
    if((l && r)){
        return nodeCount_degree2(l) + nodeCount_degree2(r) + 1;
    }
    return nodeCount_degree2(l) + nodeCount_degree2(r);
}

/*
         10
     /          \
    5           15
    / \         /  \
    3    7      12  18
    / \  / \    / \  / \
    2  4 6  8  11 14 16 19
*/