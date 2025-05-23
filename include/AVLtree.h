//UNN
//Litvyakov D. D.
//AVL Tree

#pragma once
#include <utility>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

template <typename type>
struct NodeAVL {
	int key;
	type* val;
	NodeAVL<type>* left;
	NodeAVL<type>* right;
	int height;
};

template <typename type>
int height(NodeAVL<type>* node) {
	if (node == nullptr)
		return 0;
	return node->height;
}

template <typename type>
NodeAVL<type>* newNode(int key, type val) {
	NodeAVL<type>* node = new NodeAVL<type>();
	node->key = key;
	node->val = new type(val);
	node->left = nullptr;
	node->right = nullptr;
	node->height = 1;
	return node;
}

template <typename type>
NodeAVL<type>* rightRotate(NodeAVL<type>* y) {
	NodeAVL<type>* x = y->left;
	NodeAVL<type>* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

template <typename type>
NodeAVL<type>* leftRotate(NodeAVL<type>* x) {
	NodeAVL<type>* y = x->right;
	NodeAVL<type>* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

template <typename type>
int getBalance(NodeAVL<type>* node) {
	if (node == nullptr)
		return 0;
	return height(node->left) - height(node->right);
}

template <typename type>
NodeAVL<type>* insert(NodeAVL<type>* node, int key, type val) {
	if (node == nullptr)
		return newNode(key, val);

	if (key < node->key)
		node->left = insert(node->left, key, val);
	else if (key > node->key)
		node->right = insert(node->right, key, val);
	else {
		return node;
	}

	node->height = 1 + max(height(node->left), height(node->right));

	int balance = getBalance(node);

	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	if (balance > 1 && key > node->left->key) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && key < node->right->key) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

template <typename type>
NodeAVL<type>* minValueNode(NodeAVL<type>* node) {
	NodeAVL<type>* current = node;
	while (current->left != nullptr)
		current = current->left;
	return current;
}

template <typename type>
NodeAVL<type>* deleteNode(NodeAVL<type>* root, int key) {
	if (root == nullptr) {
		return root;
	}

	if (key < root->key) {
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->key) {
		root->right = deleteNode(root->right, key);
	}
	else {
		if ((root->left == nullptr) || (root->right == nullptr)) {
			NodeAVL<type>* temp = root->left;
			if (temp == nullptr) {
				temp = root->right;
			}

			if (temp == nullptr) {
				delete root->val;
				delete root;
				return nullptr;
			}
			else {
				delete root->val;
				*root = *temp;
				delete temp;
			}
		}
		else {
			NodeAVL<type>* temp = minValueNode(root->right);
			delete root->val;
			root->key = temp->key;
			root->val = new type(*temp->val);
			root->right = deleteNode(root->right, temp->key);
		}
	}

	if (root == nullptr) {
		return root;
	}

	root->height = 1 + max(height(root->left), height(root->right));

	int balance = getBalance(root);

	if (balance > 1 && getBalance(root->left) >= 0) {
		return rightRotate(root);
	}

	if (balance > 1 && getBalance(root->left) < 0) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 && getBalance(root->right) <= 0) {
		return leftRotate(root);
	}

	if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

template <typename type>
bool findTree(NodeAVL<type>* root, int key) {
	if (root == nullptr) {
		return false;
	}
	if (root->key == key) {
		return true;
	}
	if (key < root->key) {
		return findTree<type>(root->left, key);
	}
	else {
		return findTree<type>(root->right, key);
	}
}

template <typename type>
void inorderTree(NodeAVL<type>* root) {
	if (root != nullptr) {
		inorderTree(root->left);
		cout << root->key << "(" << *root->val << ") ";
		inorderTree(root->right);
	}
}

template <typename type>
void preorderTree(NodeAVL<type>* root) {
	if (root != nullptr) {
		cout << root->key << "(" << *root->val << ") ";
		preorderTree(root->left);
		preorderTree(root->right);
	}
}

template <typename type>
void postorderTree(NodeAVL<type>* root) {
	if (root != nullptr) {
		postorderTree(root->left);
		postorderTree(root->right);
		cout << root->key << "(" << *root->val << ") ";
	}
}

template<typename type>
class AVLTree {
	NodeAVL<type>* root = nullptr;

	void clear(NodeAVL<type>* node) {
		if (node) {
			clear(node->left);
			clear(node->right);
			delete node->val;
			delete node;
		}
	}

	public:

		~AVLTree() {
			clear(root);
		}

	AVLTree(int key, type val) {
		root = newNode<type>(key, val);
	}

	bool find(int key) {
		return findTree<type>(root, key);
	}

	bool add(int key, type val) {
		if (find(key)) return false;
		root = insert<type>(root, key, val);
		return true;
	}

	void inorder() {
		inorderTree<type>(root);
	}

	void preorder() {
		preorderTree<type>(root);
	}

	void postorder() {
		postorderTree<type>(root);
	}

	bool remove(int key){
		if (!find(key)) return false;
		root = deleteNode<type>(root, key);
		return true;
	}
};

