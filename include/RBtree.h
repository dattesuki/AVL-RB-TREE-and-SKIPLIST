//UNN
//Litvyakov D. D.
//RB Tree

#pragma once
#include <utility>
#include <string>


template <typename type>
struct NodeRB {
	int key;
	type* val;
	NodeRB<type>* left;
	NodeRB<type>* right;
	//false = black
	//true = red
	bool color;
};


template <typename type>
NodeRB<type>* newNode(int key, type val) {
	NodeRB<type>* node = new NodeRB<type>();
	node->key = key;
	node->val = new type(val);
	node->left = nullptr;
	node->right = nullptr;
	node->color = false;
	return node;
}

template <typename type>
NodeRB<type>* rightRotate(NodeRB<type>* y) {

	return x;
}

template <typename type>
NodeRB<type>* leftRotate(NodeRB<type>* x) {
	NodeRB<type>* y = x->right;
	NodeRB<type>* T2 = y->left;

	y->left = x;
	x->right = T2;

	return y;
}


template <typename type>
NodeRB<type>* insert(NodeRB<type>* node, int key, type val) {
	if (node == nullptr)
		return newNode(key, val);

	if (key < node->key)
		node->left = insert(node->left, key, val);
	else if (key > node->key)
		node->right = insert(node->right, key, val);
	else {
		return node;
	}


	return node;
}

template <typename type>
NodeRB<type>* minValueNode(NodeRB<type>* node) {
	NodeRB<type>* current = node;
	while (current->left != nullptr)
		current = current->left;
	return current;
}

template <typename type>
NodeRB<type>* deleteNode(NodeRB<type>* root, int key) {
	if (root == nullptr)
		return root;

	if (key < root->key)
		root->left = deleteNode(root->left, key);
	else if (key > root->key)
		root->right = deleteNode(root->right, key);
	else {
		if ((root->left == nullptr) || (root->right == nullptr)) {
			NodeRB<type>* temp = root->left ? root->left : root->right;

			if (temp == nullptr) {
				temp = root;
				root = nullptr;
			}
			else
				*root = *temp;
			delete temp->val;
			delete temp;
		}
		else {
			NodeRB<type>* temp = minValueNode(root->right);
			root->key = temp->key;
			root->val = temp->val;
			root->right = deleteNode(root->right, temp->key);
		}
	}

	if (root == nullptr)
		return root;


	return root;
}

template <typename type>
bool findTree(NodeRB<type>* root, int key) {
	if (root->key == key) return true;
	if (key < root->key) {
		if (root->left == nullptr) return false;
		return findTree<type>(root->left, key);
	}
	if (key > root->key) {
		if (root->right == nullptr) return false;
		return findTree<type>(root->right, key);
	}
}


template <typename type>
void inorderTree(NodeRB<type>* root) {
	if (root != nullptr) {
		inorderTree(root->left);
		cout << root->key << "(" << *root->val << ") ";
		inorderTree(root->right);
	}
}

template <typename type>
void preorderTree(NodeRB<type>* root) {
	if (root != nullptr) {
		cout << root->key << "(" << *root->val << ") ";
		preorderTree(root->left);
		preorderTree(root->right);
	}
}

template <typename type>
void postorderTree(NodeRB<type>* root) {
	if (root != nullptr) {
		postorderTree(root->left);
		postorderTree(root->right);
		cout << root->key << "(" << *root->val << ") ";
	}
}

template<typename type>
class RBTree {
	NodeRB<type>* root = nullptr;

	void clear(NodeRB<type>* node) {
		if (node) {
			clear(node->left);
			clear(node->right);
			delete node->val;
			delete node;
		}
	}

public:

	~RBTree() {
		clear(root);
	}

	RBTree(int key, type val) {
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

	bool remove(int key) {
		if (!find(key)) return false;
		root = deleteNode<type>(root, key);
		return true;
	}
};

