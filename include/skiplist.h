//UNN
//Litvyakov D. D.
//

#pragma once
#include <random>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <climits>
//#define prob 0.5
using namespace std;

template <typename type>
struct Node {
	int key;
	type* val;
	std::vector<Node<type>*> Level;
	Node<type>(int _key, const type& _val): key(_key) {
		val = new type(_val);
		Level.push_back(nullptr);
	}
	~Node<type>(){
		delete val;
	}
};

bool Check(double prob) {
	std::random_device r;
	std::default_random_engine e(r());
	std::uniform_real_distribution<double> coef_gen(0., 1.);

	if (coef_gen(e) <= prob) return true;
	else return false;
}

size_t GetLevel(double prob) {
	size_t temp = 1;
	while (Check(prob)) temp++;
	return temp;
}

template <typename type>
class SkipList {
//public:
	Node<type>* head;
	double prob;

	
public:

	SkipList(double _prob = 0.5):prob(_prob) {
		head = new Node<type>(INT_MIN, type());
	}

	~SkipList() {
		Node<type>* tempNode = head;
		while (tempNode != nullptr) {
			head = tempNode;
			tempNode = tempNode->Level[0];
			delete head;
		}
	}

	bool find(int key) {
		Node<type>* tempNode = head;
		for (int i = head->Level.size() - 1; i >= 0; --i) {
			while ((tempNode->Level[i] != nullptr) && (key > tempNode->Level[i]->key)) {
				tempNode = tempNode->Level[i];
			}
		}
		if (tempNode->Level.size()!=0)		tempNode = tempNode->Level[0];
		return (tempNode != nullptr && tempNode->key == key);
	}

	bool add(int key, type val) {
		if (find(key)) return false;
		size_t tempLevel = GetLevel(prob);
		while (head->Level.size() <= tempLevel) {
			head->Level.push_back(nullptr);
		}
		Node<type>* tempNode = head;
		std::stack<Node<type>*> S;
		for (int i = head->Level.size() - 1; i >= 0; --i) {
			while (tempNode->Level[i] != nullptr && tempNode->Level[i]->key < key) {
				tempNode = tempNode->Level[i];
			}
			S.push(tempNode);
		}
		Node<type>* newNode = new Node<type>(key, val);
		newNode->Level.resize(tempLevel, nullptr); 
		for (size_t i = 0; i < tempLevel; ++i) {
			if (S.empty()) break; 
			tempNode = S.top();
			S.pop();
			newNode->Level[i] = tempNode->Level[i]; 
			tempNode->Level[i] = newNode;           
		}
		return true;
	}


	bool remove(int key) {
		if (!find(key)) return false;
		Node<type>* tempNode = head;
		std::stack<Node<type>*> S;
		for (int i = head->Level.size() - 1; i >= 0; --i) {
			while (tempNode->Level[i] != nullptr && tempNode->Level[i]->key < key) {
				tempNode = tempNode->Level[i];
			}
			S.push(tempNode);
		}
		
		Node<type>* tempNode2 = tempNode->Level[0];

		for (size_t i = 0; i < tempNode2->Level.size(); ++i) {
			if (S.empty()) break;
			tempNode = S.top();
			S.pop();
			tempNode->Level[i] = tempNode2->Level[i];
		}

		delete tempNode2;

		return true;
	}

	void print() const {
		int maxLevel = head->Level.size();
		for (int lvl = maxLevel - 1; lvl >= 0; --lvl) {
			Node<type>* current = head;
			std::cout << "Level " << lvl << ": ";
			while (current->Level.size() > lvl && current->Level[lvl] != nullptr) {
				current = current->Level[lvl];
				std::cout << "(" << current->key << ", " << *(current->val) << ") ";
			}
			std::cout << std::endl;
		}
	}


	size_t size() {
		size_t sz = 0;
		Node<type>* current = head->Level[0];
		while (current != nullptr) {
			sz++;
			current = current->Level[0];
		}
		return sz;
	}
};