#include"BST.h"
int main() {
	BST* binTree = new BST{};
	// binTree->Insert(4, binTree);
	// binTree->Insert(5, binTree);
	// binTree->DeleteNode(binTree, 4);
	BST *tmp = binTree->left;
	tmp = new BST{nullptr, nullptr, binTree, 5};
	cout << 5;
}