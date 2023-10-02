#include <iostream>
#include <fstream>
#include <string>
#include<stack>
#include<queue>
using namespace std;

// �������ڵ�����ݽṹ
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    bool flag;
    int LTag, RTag;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr), flag(true), LTag(0), RTag(0) {}
};

void deleteTree(TreeNode* root);
// ����ڵ㵽������, ����������
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

// ���ļ��ж�ȡ���ݲ�����������
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

// ���ֵݹ�����㷨�����ڶԷǵݹ��㷨����֤��
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
//��������ķǵݹ�д��
void inorder_iterative(TreeNode* root){
    stack<TreeNode* > st;
    stack<int> statuses;   //���ڴ��ÿ���ڵ��״̬����Ϊ1������������û�б�������ʱ��Ӧ�ô�ӡ���ڵ��data���������������������������Ѿ��������ڵ㱻pop��
    st.push(root);
    statuses.push(1);
    while(!st.empty()){
        TreeNode* t = st.top();
        int status = statuses.top();
        if(status == 1){ // �ڵ�һ��ʼ����״̬Ϊ1
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

//��������ǵݹ��㷨�ĸĽ������ϰ汾��
void inorder_iterative_2th(TreeNode* root){//�Ľ��������������ռ临�Ӷȱ�С��
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

//��������ķǵݹ�д����ǰ������ǵݹ����������ǵݹ�д�����ƣ�ֻ��ı��ӡ�ڵ�dataֵ��˳����У�
void postorder_iterative(TreeNode* root){ // ����������ǰ�����������������ѵ���������ȷ����ʱ�ô�ӡ�ڵ��dataֵ��һ����˵���ڵ�������״̬���ֱ���δ��������������ʱ�����һ��if
//�����������ı�����δ���������������������������ꡣ���У�������״ֻ̬�ܽ���һ���������λ�����֡�ÿ��node�ڵ�����flag��ǣ�flagΪ��ʱ������Ϊ2״̬������Ϊ3״̬��
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
                //��ʼ����������
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
    string filename = "input_tree.txt"; // �滻�������ļ���
    TreeNode* root = buildTreeFromFile(filename);

    cout << "Postorder traversal of the binary tree: ";
    postorderTraversal(root);
    cout << endl;
    cout << "Postorder_Non_recursive of the tree: " << endl;
    postorder_iterative(root);
    cout << endl;
    cout << "��Ϊ2�Ľڵ����Ϊ: " << nodeCount_degree2(root) << endl;
    cout << "��Ϊ1�Ľڵ����Ϊ: " << nodeCount_degree1(root) << endl;
    cout << "��Ϊ0�Ľڵ����Ϊ: " << nodeCount_degree0(root) << endl;
    cout << "�ܽڵ����Ϊ: " << nodeCount(root) << endl;
    cout << "�������Ϊ: " << depth(root) << endl;
    // �����ڴ棨��ѡ��
    // TODO: ��д�ͷ��ڴ�ĺ���
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

int depth(TreeNode *root){//�����������
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