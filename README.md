# Binary Search Tree
This is the code that I learned.

## 1\. Files
* BinarySearchTree.h: class for Binary Search Tree
* TreeNode.h: class for TreeNode
* main.cpp: main function for test

## 2\. If You Want to Compile with Visual Studio
**\_CRT\_SECURE\_NO\_WARNINGS** has to be added to preprocessor definitions.

## 3\. insert
```cpp
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
```

![insert](https://sooseongcom.com/assets/images/20240101/1.PNG)\
Time complexity of insert() is O(h). (h: height)

## 4\. delete
```cpp
template <class T>
void BinarySearchTree<T>::deletion(T data) {
	TreeNode<T>* p = m_root, * pp = NULL;	//p: the node to delete	//pp: the parent of p

	while (p && data != p->m_data) {
		pp = p;
		if (data < p->m_data) p = p->m_left;
		else p = p->m_right;	// data >= p->m_data
	}
```

### 4.1. not found
```cpp
if (p == NULL) return;	//(1) not found
```

### 4.2. if p is a degree 0 node (p is leaf)
```cpp
if (p->m_left == 0 && p->m_right == 0) {	//(2) p is leaf
    if (pp == 0) m_root = 0;
    else if (pp->m_left == p) pp->m_left = 0;
    else pp->m_right = 0;

    delete p;
    return;
}
```

![p is leaf](https://sooseongcom.com/assets/images/20240101/2.PNG)

### 4.3. if p is a degree 1 node
```cpp
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
```

![p has only right child](https://sooseongcom.com/assets/images/20240101/3.PNG)

### 4.4. if p is a degree 2 node (p has both left and right child)
```cpp
//(4) p has both left and right child
TreeNode<T>* prevprev = p, * prev = p->m_right, * curr = p->m_right->m_left;

while (curr) {
    prevprev = prev;
    prev = curr;
    curr = curr->m_left;
}
```

![p has both left and right child take-1](https://sooseongcom.com/assets/images/20240101/4.PNG)

![p has both left and right child take-2](https://sooseongcom.com/assets/images/20240101/5.PNG)

```cpp
/* now, curr == 0
 * prev is the node to be deleted
 * prevprev is prev's parent
 * prev->m_left==0
 */
```

![now, curr is equal to 0](https://sooseongcom.com/assets/images/20240101/6.PNG)\
The node p is replace by either the largest node in its left subtree or the smallest node in its right subtree. By this source code, the node p is replace by the largest node in its left subtree. prev's data is going to be moved to p. And then, prev is the node to be deleted.

```cpp
    p->m_data = prev->m_data;
	if (prevprev == p) prevprev->m_right = prev->m_right;
	else prevprev->m_left = prev->m_right;
	delete prev;
	return;
}
```

![delete 20](https://sooseongcom.com/assets/images/20240101/7.PNG)

## 5\. operator\<< overloading
For BST which is BinarySearchTree, ```cout << BST``` runs ```cout << BST.m_root```.\
For treenode which is TreeNode, ```cout << treenode``` prints a Binary Search Tree whose root is treenode.

```cpp
//BinarySearchTree.h Line 23~30
friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree<T>& tree) {
    //InOrder
    TreeNode<T>* t = tree.m_root;

    os << t;

    return os;
}
```

```cpp
//TreeNode.h Line 28~49
friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree<T>& tree) {
    //InOrder
    TreeNode<T>* t = tree.m_root;

    os << t;

    return os;
}
```
operator\<<() of TreeNode.h do an InOrder Traversal.

## 6\. Destructor
The destructor calls **BinarySearchTree\<T>::deletePostOrder(TreeNode\<T>\* t)**. **BinarySearchTree\<T>::deletePostOrder(TreeNode\<T>\* t)** do an InOrder Traversal.

```cpp
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
```

## 7\. Reference
1\) Pubby. 2012. "Class template with template class friend, what's really going on here?", stackoverflow. (2024. 01. 01. visited). <https://stackoverflow.com/questions/8967521/class-template-with-template-class-friend-whats-really-going-on-here>{: target="_blank"}