//�޸���2023/10/01, �����������Ĺ�������Ķ�����BST.hͷ�ļ��С����У���Ҫ�ѵ����ڽ���ɾ��������

//ɾ����Ҫ������������ۣ�1. ��ɾ���Ľ��û�������������������ߴ�ɾ���Ľ��ΪҶ��㡣��һ��ϸ��Ϊ��ɾ���Ϊ���ڵ�ͽ�㲻Ϊ���ڵ㡣����㲻Ϊ����㣬����Ҫ���丸�ڵ�����ָ����º�Ľ�㡣
//2. ��ɾ���Ľڵ��������������ڣ���ʱ�������������˳���ô�ɾ�����������������ҽڵ����˽ڵ㣬ԭ���ҽڵ���ɾ����
//�������ҽڵ���������������丸�����Ҳࡣ�����һ��ϸ��Ϊ�����ҽڵ㸸�ڵ�Ϊ��ɾ�ڵ�ͷǴ�ɾ�ڵ㡣

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
		//�������������ڵ��������������£�������¸�����ָ��ֱ��return����Ϊ���ҽ������ɾ��㱻ɾ����
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
		//��ɾ��� �Ǹ���㣬 ���丸�������ָ���½��
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

 