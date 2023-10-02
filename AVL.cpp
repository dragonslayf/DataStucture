//By Xie Tianyang, ʹ��ʱ�������Ľڵ�ֵ������Ϊ���������Ϊ0-9������չʾ������ܻ�ȱʧ��
//AVL���ĺ�������ƽ������������ܱ�֤ÿ�ε�����������Сʧ�����������������ڵ������ʧ���������

//������Ϊ4��������ֱ�Ϊ��LL��RR, LR, RL
//LL���������½ڵ������ʧ��ڵ����ڵ���������� ��Ҫ�����ʧ�������һ������ת
//RR, �������½ڵ������ʧ������ҽڵ���������� ��Ҫ�����ʧ�������һ������ת��
//LR, �����½ڵ������ʧ��ڵ����ڵ������������Ҫ�ȶ����ʧ��ڵ���Һ��ӽ�������ת���ٶ�ʧ��ڵ��������ת��
//RL, �����½ڵ������ʧ��ڵ���ҽڵ������������Ҫ�ȶ�ʧ��ڵ�����ӽ�������ת���ٶ�ʧ��ڵ��������ת��

//����ƽ��ĺ������ڽ���ƽ��Ľڵ����ƣ�����֤��������������в��䡣
#include"AVL.h"

void AVL::LRotate(AVL* f){
	AVL* c = f->right;
	AVL *a1 = f->left, *a2 = c->left, *a3 = c->right;
	int tmp = c->data;
	c->data = f->data;
	f->data = tmp; // �������ڵ�ֱ�ӽ�����ֵ��
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
	f->data = tmp; // �������ڵ�ֱ�ӽ�����ֵ��
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
	//AVL���Ĳ������������������BST������ͬ������Ҫ��Ѱ�Ҳ����λ��;�и���ÿ���ڵ��ƽ������ֵ��
	bool isDone = false;
	AVL* lastest = nullptr;
	if (!begin) {
		begin = new AVL{ nullptr, nullptr, x };
		return;
	}
	while (!isDone && begin) {
		if (x > begin->data) {
			 // ��֪������������Ϊ�պ͸���ƽ������С��-1�������ì�ܡ�
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
			//��ʼƽ�������
			if(lastest->balancefactor < 0){
				//LR��ת, ������һ�Σ�������һ��
				LRotate(lastest);
			}
			//LL��ת, ����һ��
			RRotate(begin);
			//break;//?
		}
		else if(begin->balancefactor < -1){
			lastest = begin->right;
			if(lastest->balancefactor > 0){
				//RL��ת��������һ�Σ�������һ��
				RRotate(lastest);
			}
			//RR��ת,����һ��
			LRotate(begin);
			//break;//?
		}
	}

}

int main(){
	AVL* binTree = new AVL{nullptr, nullptr, 15};
	//�������ݣ�3 7 10 9 8 -1.
	int t;
	while(cin >> t && t != -1){
		binTree->Insert(t, binTree);
	}
	printBiTree(binTree);
}