//修改于2023/10/01, 二叉排序树的构建，类的定义在BST.h头文件中。其中，主要难点在于结点的删除操作。

//删除主要分两种情况讨论：1. 待删除的结点没有左子树或右子树或者待删除的结点为叶结点。进一步细分为待删结点为根节点和结点不为根节点。若结点不为根结点，则需要令其父节点重新指向更新后的结点。
//2. 待删除的节点左右子树均存在，此时根据中序遍历的顺序，用待删除结点的左子树的最右节点代替此节点，原最右节点则被删除。
//并将最右节点的左子树交付给其父结点的右侧。这里进一步细分为：最右节点父节点为待删节点和非待删节点。

#include"BST.h"

void Insert(int x, BST *begin) {
	bool isDone = false;
	if (!begin) {
		begin = new BST{ nullptr, nullptr, nullptr, x };
		return;
	}
	while (!isDone && begin) {
		if (x > begin->data) {
			if (begin->right) {
				begin = begin->right;
			}
			else {
				begin->right = new BST{ nullptr, nullptr, begin, x };
				isDone = true;
			}
		}
		else if (x < begin->data) {
			if (begin->left) {
				begin = begin->left;
			}
			else {
				begin->left = new BST{ nullptr, nullptr, begin, x };
				isDone = true;
			}
		}
		else {
			cout << "failed!" << endl;
			return;
		}
	}
	if (!isDone) cout << "failed!" << endl;
	return;

}
BST* BST::positionFind(BST* head, int x ) {
	while (head) {
		if (x == head->data) break;
		if (x > head->data) head = head->right;
		else head = head->left;
	}
	return head;
}
BST* BST::findMin( BST* head) {
	if (!head) return nullptr;
	while (head->left) {
		head = head->left;
	}
	return head;
}
BST* BST::findMax(BST* head) {
	if (!head) return nullptr;
	while (head->right) {
		head = head->right;
	}
	return head;
}
void BST::DeleteNode(BST* begin, int x) {
	begin = begin->positionFind(this, x);
	BST *waste = begin;
	if (!begin) {
		cout << "Node not found!" << endl;
		return;
	}
	BST* f = begin->father;
	if (!begin->left && !begin->right) {
		waste = begin;
		begin = nullptr;
	}
	else if (begin->left && !begin->right) {
		waste = begin;
		begin = begin->left;
	}
	else if (!begin->left && begin->right) {
		waste = begin;
		begin = begin->right;
	}
	else {
		//左右子树均存在的情况，这种情况下，无需更新父结点的指向，直接return。因为最右结点代替待删结点被删除。
		BST *s = begin->findMax(begin->left);
		if(s->father == begin){
			begin->left = s->left;
		}
		else{
			s->father->right = s->left;
		}
		begin->data = s->data;
		delete s;
		return;
	}
	if(f){
		//待删结点 非根结点， 令其父结点重新指向新结点
		if(f->left == waste){
			f->left = begin;
		}
		else if(f->right == waste){
			f->right = begin;
		}
		delete waste;
	}
}

int main() {
	BST* binTree = new BST{nullptr, nullptr, nullptr, 5};
	int t;
	while(cin >> t && t != -1){
		Insert(t, binTree);
	}
	printBiTree(binTree);
	binTree->DeleteNode(binTree, 5);
	printBiTree(binTree);
}

 