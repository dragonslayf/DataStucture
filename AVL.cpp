//By Xie Tianyang, 使用时输入树的节点值，必须为整数，最好为0-9，否则展示结果可能会缺失。
//AVL树的核心在于平衡调整。并且能保证每次调整均调整最小失衡树。即，距离插入节点最近的失衡结点的树。

//调整分为4种情况，分别为：LL，RR, LR, RL
//LL，即插入新节点至最近失衡节点的左节点的左子树， 需要对最近失衡结点进行一次右旋转
//RR, 即插入新节点至最近失衡结点的右节点的右子树， 需要对最近失衡结点进行一次左旋转。
//LR, 插入新节点至最近失衡节点的左节点的右子树，需要先对最近失衡节点的右孩子进行左旋转，再对失衡节点进行右旋转。
//RL, 插入新节点至最近失衡节点的右节点的左子树，需要先对失衡节点的左孩子进行右旋转，再对失衡节点进行左旋转。

//保持平衡的核心在于将不平衡的节点上移，并保证树的中序遍历序列不变。
#include"AVL.h"

void AVL::LRotate(AVL* f){
	AVL* c = f->right;
	AVL *a1 = f->left, *a2 = c->left, *a3 = c->right;
	int tmp = c->data;
	c->data = f->data;
	f->data = tmp; // 两个主节点直接交换数值。
	f->left = c; f->right = a3;
	c->left = a1; c->right = a2;
	if(a3)	a3->father = f;
	if(a1)	a1->father = c;
}

void AVL::RRotate(AVL* f){
	AVL *c = f->left;
	AVL *a1 = c->left, *a2 = c->right, *a3 = f->right;
	int tmp = c->data;
	c->data = f->data;
	f->data = tmp; // 两个主节点直接交换数值。
	f->left = a1; f->right = c;
	c->left = a2; c->right = a3;
	if(a1) a1->father = f;
	if(a3) a3->father = c;
}

int AVL::height(AVL* head) {
	if (!head) {
		return 0;
	}
	else {
		return max(height(head->left), height(head->right)) + 1;
	}
}
void AVL::isBalanced(AVL* head) {
	if (!head) {
		return;
	}
	int a1 = height(head->left), a2 = height(head->right);
	head->balancefactor = a1 - a2;
	head->h = max(a1, a2) + 1;
	
}
void AVL::Insert(int x, AVL* begin) {
	//AVL树的插入操作，基础操作和BST插入相同，但是要在寻找插入点位的途中更新每个节点的平衡因子值。
	bool isDone = false;
	AVL* lastest = nullptr;
	if (!begin) {
		begin = new AVL{ nullptr, nullptr, x };
		return;
	}
	while (!isDone && begin) {
		if (x > begin->data) {
			 // 已知，根的右子树为空和根的平衡因子小于-1两种情况矛盾。
			if(begin->right){
				begin = begin->right;
				continue;
			}
			begin->right = new AVL{nullptr, nullptr, x};
			begin->right->father = begin;
			begin = begin->right;
			isDone = true;
		}
		else if (x < begin->data) {
			if(begin->left){
				begin = begin->left;
				continue;
			}
			begin->left = new AVL{nullptr, nullptr, x};
			begin->left->father = begin;
			begin = begin->left;
			isDone = true;
		}
		else {
			cout << "Insertion falied, Identical node with data " << x << "exists." << endl;
			isDone = true;
		}
	}
	while(begin->father){
		begin = begin->father;
		begin->isBalanced(begin);
		if(begin->balancefactor > 1){
			lastest = begin->left;
			//开始平衡操作。
			if(lastest->balancefactor < 0){
				//LR旋转, 先左旋一次，再右旋一次
				LRotate(lastest);
			}
			//LL旋转, 右旋一次
			RRotate(begin);
			//break;//?
		}
		else if(begin->balancefactor < -1){
			lastest = begin->right;
			if(lastest->balancefactor > 0){
				//RL旋转，先右旋一次，再左旋一次
				RRotate(lastest);
			}
			//RR旋转,左旋一次
			LRotate(begin);
			//break;//?
		}
	}

}

int main(){
	AVL* binTree = new AVL{nullptr, nullptr, 15};
	//测试数据：3 7 10 9 8 -1.
	int t;
	while(cin >> t && t != -1){
		binTree->Insert(t, binTree);
	}
	printBiTree(binTree);
}