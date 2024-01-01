#ifndef BST
#define BST

#include "TreeNode.h"
#include <iostream>

using namespace std;

//prototype
template <class T>
class BinarySearchTree {
private:
	TreeNode<T>* m_root;
	void deletePostOrder(TreeNode<T>* t);	//for destructor

public:
	BinarySearchTree() { m_root = NULL; }
	virtual ~BinarySearchTree();

	void insert(T data);
	void deletion(T data);

	friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree<T>& tree) {
		//InOrder
		TreeNode<T>* t = tree.m_root;

		os << t;

		return os;
	}
};

//definition

template <class T>
void BinarySearchTree<T>::deletePostOrder(TreeNode<T>* t) {
	if (t != NULL) {
		deletePostOrder(t->m_left);
		deletePostOrder(t->m_right);
		delete t;
	}
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree() {
	deletePostOrder(m_root);
}

template <class T>
void BinarySearchTree<T>::insert(T data) {
	TreeNode<T>* p = m_root, * pp = NULL;	//pp: the parent of p
	while (p) {
		pp = p;
		if (data < p->m_data) p = p->m_left;
		else p = p->m_right;	// data >= p->m_data
	}

	//Perform insertion
	p = new TreeNode<T>(data);
	if (m_root != NULL) {	//tree not empty
		if (data < pp->m_data) pp->m_left = p;
		else pp->m_right = p;	// data >= p->m_data
	}
	else {
		m_root = p;
	}
}

template <class T>
void BinarySearchTree<T>::deletion(T data) {
	TreeNode<T>* p = m_root, * pp = NULL;	//p: the node to delete	//pp: the parent of p

	while (p && data != p->m_data) {
		pp = p;
		if (data < p->m_data) p = p->m_left;
		else p = p->m_right;	// data >= p->m_data
	}

	if (p == NULL) return;	//(1) not found

	if (p->m_left == 0 && p->m_right == 0) {	//(2) p is leaf
		if (pp == 0) m_root = 0;
		else if (pp->m_left == p) pp->m_left = 0;
		else pp->m_right = 0;

		delete p;
		return;
	}

	if (p->m_left == 0) {	//(3-1) p has only right child
		if (pp == 0) m_root = p->m_right;
		else if (pp->m_left == p) pp->m_left = p->m_right;
		else pp->m_right = p->m_right;

		delete p;
		return;
	}

	if (p->m_right == 0) {	//(3-2) p has only left child
		if (pp == 0) m_root = p->m_left;
		else if (pp->m_left == p) pp->m_left = p->m_left;
		else pp->m_right = p->m_left;

		delete p;
		return;
	}

	//(4) p has both left and right child
	TreeNode<T>* prevprev = p, * prev = p->m_right, * curr = p->m_right->m_left;

	while (curr) {
		prevprev = prev;
		prev = curr;
		curr = curr->m_left;
	}

	/* now, curr == 0
	 * prev is the node to be deleted
	 * prevprev is prev's parent
	 * prev->m_left==0
	 */

	p->m_data = prev->m_data;
	if (prevprev == p) prevprev->m_right = prev->m_right;
	else prevprev->m_left = prev->m_right;
	delete prev;
	return;
}

#endif