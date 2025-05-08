//UNN
//Litvyakov D. D.
//

#pragma once
#include <utility>

template <typename type> 
class Node {
	std::pair<size_t, type> data;
	Node<type>* prev, left, right;
	size_t height = 1;
public:
	Node(size_t v1, const type& v2, Node* _prev = nullptr) {
		data = std::make_pair(v1, v2);
		prev = _prev;
		left = nullptr;
		right = nullptr;
	}
	template <typename T>
	friend class Tree;
	template <typename T>
	friend class AVLTree;
};


template <typename type>
class Tree {
protected:
	Node<type>* root;
	size_t sz;

public:
	Tree(size_t v1, const type& v2){
		root = new Node(v1, v2);
		sz = 1;
	}

	//bool Add(size_t v1, const type& v2) {
	//	if (v1 == data.first) return false;
	//	if (v1 > data.first) {
	//		if (right != nullptr) right->Add(v1, v2);
	//		else right = new Node(v1, v2);
	//	}
	//	else {
	//		if (left != nullptr) left->Add(v1, v2);
	//		else left = new Node(v1, v2);
	//	}
	//	return true;
	//}
};

template <typename type>
class AVLTree: public Tree<type> {

public:
	AVLTree(size_t v1, const type& v2) :Tree(v1, v2) {};

};