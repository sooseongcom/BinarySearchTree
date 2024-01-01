#ifndef TREENODE
#define TREENODE

#include <iostream>

template <class T>
class TreeNode
{
	template <class U>
	friend class BinarySearchTree;
private:
	T m_data;
	TreeNode* m_left;
	TreeNode* m_right;
public:
	TreeNode() :m_left(NULL), m_right(NULL) {}
	virtual ~TreeNode() { }
	TreeNode(T& data, TreeNode* left = NULL, TreeNode* right = NULL)
	{
		this->m_data = data;
		this->m_left = left;
		this->m_right = right;
	}

	TreeNode* getLeftNode() const { return m_left; }
	TreeNode* getRightNode() const { return m_right; }

	friend std::ostream& operator<<(std::ostream& os, const TreeNode* node)
	{
		TreeNode<T>* left = 0, * right = 0;

		//InOrder
		if (node != NULL) {
			left = node->getLeftNode();
			if (left != NULL) {
				os << left << ' ';
			}
			
			os << node->m_data << ' ';
			
			right = node->getRightNode();
			if (right != NULL) {
				os << right << ' ';
			}
		}

		return os;
	}
};

#endif