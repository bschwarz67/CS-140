#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include "bstree.h"
using namespace std;

BSTree::BSTree()
{
  sentinel = new BSTNode;
  sentinel->parent = NULL;
  sentinel->left = NULL;
  sentinel->right = sentinel;
  size = 0;
}

BSTree::~BSTree()
{
  recursive_destroy(sentinel->right);
  delete sentinel;
}

int BSTree::Insert(string s, void *val)
{
  BSTNode *parent;
  BSTNode *n;

  parent = sentinel;
  n = sentinel->right;

  while (n != sentinel) {
    if (n->key == s) return 0;
    parent = n;
    if (s < n->key) {
      n = n->left;
    } else {
      n = n->right;
    }
  }

  n = new BSTNode;
  n->key = s;
  n->val = val;
  n->parent = parent;
  n->left = sentinel;
  n->right = sentinel;
  if (parent == sentinel) {
    sentinel->right = n;
  } else if (s < parent->key) {
    parent->left = n;
  } else {
    parent->right = n;
  }
  size++;
  return 1;
}

void *BSTree::Find(string s)
{
  BSTNode *n;

  n = sentinel->right;
  while (1) {
    if (n == sentinel) return NULL;
    if (s == n->key) return n->val;
    if (s < n->key) {
      n = n->left;
    } else {
      n = n->right;
    }
  }
}

int BSTree::Delete(string s)
{
  BSTNode *n, *parent, *mlc;
  string tmpkey;
  void *tmpval;

  n = sentinel->right;
  while (n != sentinel && s != n->key) {
    if (s < n->key) {
      n = n->left;
    } else {
      n = n->right;
    }
  }
  if (n == sentinel) return 0;

  parent = n->parent;
  if (n->left == sentinel) {
    if (n == parent->left) {
      parent->left = n->right;
    } else {
      parent->right = n->right;
    }
    if (n->right != sentinel) n->right->parent = parent;
    delete n;
    size--;
  } else if (n->right == sentinel) {
    if (n == parent->left) {
      parent->left = n->left;
    } else {
      parent->right = n->left;
    }
    n->left->parent = parent;
    delete n;
    size--;
  } else {
    for (mlc = n->left; mlc->right != sentinel; mlc = mlc->right) ;
    tmpkey = mlc->key;
    tmpval = mlc->val;
    Delete(tmpkey);
    n->key = tmpkey;
    n->val = tmpval;
  }
  return 1;
}

vector <void *>BSTree::Sorted_Vector()
{
  array.clear();
  recursive_make_vector(sentinel->right);
  return array;
}

void BSTree::Print()
{
  recursive_inorder_print(0, sentinel->right);
}



/*wrapper method that uses recursive postorder method to print tree preorder*/
void BSTree::Postorder() {
	recursive_postorder(0, sentinel->right);
}

/*wrapper method that uses recursive_preorder method to print tree preorder*/
void BSTree::Preorder() {
	recursive_preorder(0, sentinel->right);
}

/*returns the depth of the node specified by key. if no node specified by key exists, returns -1*/
int BSTree::Depth(string key) {
	BSTNode *n = sentinel->right;
	int depth = 0;
	
	while(n != sentinel) {
		
		if(n->key == key) {
			return depth;
		}

		if(key < n->key) {
			depth++;
			n = n->left;
		}
		else {
			depth++;
			n = n->right;
		}
	}
	return -1;
}

/*wrapper method that calls recursive_height method to find the height of the tree.
returns height of the tree, returns -1 if tree is empty.*/
int BSTree::Height() {
	return recursive_height(sentinel->right);
}

/*wrapper method that calls recursive_height_and_avl_check method. 
Returns 0 if tree is not avl, returns 1 if it is*/
int BSTree::IsAVL() {
	if(recursive_height_and_avl_check(sentinel->right) == -2) return 0;
	return 1;
}

/*performs AVL tree style rotation about a node designated by key. returns 0 if node
designated by key does not exist or is root. returns 1 when rotation is complete*/
int BSTree::Rotate(string key) {
	BSTNode *n;
	
	n = sentinel->right;
	while (1) {		//find node n designated by key, return 0 is key deisgates root or a node that doesnt exist
		if (n == sentinel) return 0;
		if (key == n->key) break;
		if (key < n->key) {
			n = n->left;
		} 
		else {
			n = n->right;
		}
	}
	
	if(n->parent->right == n) {		//rotation about n if n is right child of its parent				
		if(n->parent->parent->right == n->parent) {
			n->parent->parent->right = n;
		}
		else {
			n->parent->parent->left = n;
		}
		n->parent->right = n->left;
		n->left->parent = n->parent;
		n->left = n->parent;
		n->parent = n->parent->parent;
		n->left->parent = n;
	
	}
	else {		//rotation about n if n is left child of its parent
		if(n->parent->parent->right == n->parent) {
			n->parent->parent->right = n;
		}
		else {
			n->parent->parent->left = n;
		}
		n->parent->left = n->right;
		n->right->parent = n->parent;
		n->right = n->parent;
		n->parent = n->parent->parent;
		n->right->parent = n;
	
	}

	return 1;
	


}

int BSTree::Size()
{
  return size;
}

int BSTree::Empty()
{
  return (size == 0);
}

/*recursive postorder print.*/ 
void BSTree::recursive_postorder(int level, BSTNode *n) {
	if(n == sentinel) {		//base case: return if leaf node is reached
		return;
	}
	recursive_postorder(level + 2, n->left);	//traverse left subtree
	recursive_postorder(level + 2, n->right);	//traverse right subtree
  	printf("%*s%s\n", level, "", n->key.c_str());	//each key printed preceded by #spaces = 2 * depth of node	
}

/*recursive preorder print.*/
void BSTree::recursive_preorder(int level, BSTNode *n) {
	if(n == sentinel) {		//base case: return if lead node is reached
		return;
	}
  	printf("%*s%s\n", level, "", n->key.c_str());	//each key printed preceded by #spaces = 2 * depth of node	
	recursive_preorder(level + 2, n->left);		//traverse left subtree
	recursive_preorder(level + 2, n->right);	//traverse right subtree
}

/*recursive function that returns height of node n or -1 if tree is empty*/
int BSTree::recursive_height(BSTNode *n) {
	int leftSubTreeHeight;
	int rightSubTreeHeight;

	
	if(n == sentinel) {		//base case: return -1 if leaf node is reached
		return -1;
	}

	leftSubTreeHeight = recursive_height(n->left) + 1;		//get height of left subtree, increment height by 1
	rightSubTreeHeight = recursive_height(n->right) + 1;	//get height of right subtree, increment height by 1

	if(leftSubTreeHeight > rightSubTreeHeight) {	//return maximum height between left, right subtree
		return leftSubTreeHeight;
	}
	else {
		return rightSubTreeHeight;
	}
}



int BSTree::recursive_height_and_avl_check(BSTNode *n) {
	int leftHeight = 0, rightHeight = 0;

	if(n == sentinel) {		//base case: return 0 if leaf node is reached
		return 0;
	}
	else {		//in all other cases, get height of left and right subtrees
		leftHeight = recursive_height_and_avl_check(n->left)
		rightHeight = recursive_height_and_avl_check(n->right);
	}
	if(leftHeight == -2 || rightHeight == -2){		//if subtree has already been found to not be AVL, dont check if current subtree is AVL, just return -2
		return -2;
	}
	else if(leftHeight - rightHeight < -1 || leftHeight - rightHeight > 1) {	//return -2 if the difference between the height of any two subtrees exceeds 1
		return -2;
	}
	else {
		if(leftHeight > rightHeight) {		//last case: tree is considered AVL to this point, return maximum height of two subtrees incremented by 1
			return leftHeight + 1;
		}
		return rightHeight + 1;
	}
}



void BSTree::recursive_inorder_print(int level, BSTNode *n)
{
  if (n == sentinel) return;
  recursive_inorder_print(level+2, n->right);
  printf("%*s%s\n", level, "", n->key.c_str());
  recursive_inorder_print(level+2, n->left);
}

void BSTree::recursive_make_vector(BSTNode *n)
{
  if (n == sentinel) return;
  recursive_make_vector(n->left);
  array.push_back(n->val);
  recursive_make_vector(n->right);
}

void BSTree::recursive_destroy(BSTNode *n)
{
  if (n == sentinel) return;
  recursive_destroy(n->left);
  recursive_destroy(n->right);
  delete n;
}
