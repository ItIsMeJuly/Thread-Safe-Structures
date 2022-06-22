#pragma once
#include <iostream>
#include <thread>
#include <array>
#include <queue>
#include <vector>
#include <mutex>

struct node {
	std::string text;
	node* first;
	node* sec;

	node(std::string val) : text(val) {
		first = NULL;
		sec = NULL;
	}
};

class tree {
	node* root;
	std::mutex m;
public:

	static tree createTree(const std::string& text, const std::string& value) {
		tree Tree;
		Tree.root = new node{ value };
		return Tree;
	}

	static node* find(node* root, const std::string value) {
		std::lock_guard<std::mutex> l(m);
		if (root == nullptr)
			return NULL;
		if (root->text == value)
			return root;
		auto firstFound = tree::find(root->first, value);
		if (firstFound != NULL)
			return firstFound;
		return tree::find(root->sec, value);
	}

	bool addSubroot(const std::string& head, const std::string& subroot) {
		std::lock_guard<std::mutex> l(m);
		node headNode = tree::find(root, head);
		if (!headNode)
			return false;
		if (headNode->first && headNode->sec)
			return false;
		if (!headNode->first)
			headNode->first = new node{ subroot };
		else
			headNode->sec = new node{ subroot };
	}

	static void traverse(node* start) {
		std::lock_guard<std::mutex> lk{ m };
		if (!start)
			return;
		std::queue<node*> q;
		q.push(start);
		while (!q.empty()) {
			unsigned long size = q.size();
			for (int i = 0; i < size; i++) {
				auto current = q.front();
				q.pop();
				std::cout << current->text << std::endl;
				if (current->first)
					q.push(current->first);
				if (current->sec)
					q.push(current->sec);
			}
			std::cout << std::endl;
		}
	}
};
