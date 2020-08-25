#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
#include<filesystem>
#include<queue>
#include"QuickSearchTree.h"
namespace fs = std::experimental::filesystem;
using namespace std;
class ntNode {
public:
	string key;
	string path;
	vector<ntNode*>* childs;
	friend ostream& operator <<(ostream& out, const ntNode& curr) {
		out << "Name:" << curr.key << endl;
		out << "Path:" << curr.path << endl;
		return out;
	}
	ntNode() {
		key = "";
		path = "";
		childs = NULL;
	}
	~ntNode() {
		delete childs;
	}
	
};

class nTree {
	ntNode* root;
	QuickSearchTree* fileTree;
	
	void inOrder(ntNode* p) {
		if (p != NULL) {
			int treeDivision = (p->childs->size()) / 2;
			int i = 0;
			for (vector<ntNode*>::iterator it = p->childs->begin();it!=p->childs->end();++it) {
				if (i < treeDivision) {
					inOrder((*it));
					cout << *p;
				}
				else {
					cout << *(*it);
					inOrder(*it);
				}
				++i;
			}
		}
	}
	void preOrder(ntNode* p) {
		if (p != NULL) {
			int treeDivision = (p->childs->size() / 2);
			int i = 0;
			cout << *p;
			for (vector<ntNode*>::iterator it = p->childs->begin(); it != p->childs->end(); ++it) {
				if (i < treeDivision) {
					preOrder(*it);
					
				}
				else {
					preOrder(*it);
				}
				++i;
			}
		}
	}
	void postOrder(ntNode* p) {
		if (p != NULL) {
			int treeDivision = (p->childs->size() / 2);
			int i = 0;
			for (vector<ntNode*>::iterator it = p->childs->begin(); it != p->childs->end(); ++it) {
				if (i < treeDivision) {
					postOrder((*it));

				}
				else {
					postOrder(*it);
				}
				++i;
			}
			cout << *p;
		}
	}
	void levelOrder(ntNode* p) {
		cout << *p;
		queue<ntNode*> myqueue;
		for (vector<ntNode*> ::iterator it = p->childs->begin(); it != p->childs->end(); ++it)
			myqueue.push(*(it));
		while (!myqueue.empty()) {
			ntNode* top = myqueue.front();
			myqueue.pop();
			cout << *top;
			for (vector<ntNode*> ::iterator it = top->childs->begin(); it != top->childs->end(); ++it)
				myqueue.push(*(it));
		}
	}
	void build_Tree(ntNode* curr,string path) {
		for (auto& currPath : fs::directory_iterator(path)) {
			ntNode* newNode = new ntNode;
			fs::path curr1 = currPath;
			newNode->key = curr1.filename().generic_string();
			newNode->path = curr1.generic_string();
			newNode->childs = new vector<ntNode*>;
			curr->childs->push_back(newNode);
			if (!curr1.has_extension()) {
				build_Tree(newNode, newNode->path);
			}
			else {
				fileTree->Insert(newNode->key, newNode->path);
			}
		}
	}
public:
	nTree(string path) {
		root = new ntNode();
		fileTree = new QuickSearchTree;
		root->path = path;
		fs::path keyPath = path;
		root->key = keyPath.filename().generic_string();
		root->childs = new vector<ntNode*>;
		build_Tree(root, root->path);
	}
	void insert(string Where,string path) {
		ntNode* finded = find(Where);
		fs::path curr = path;
		if (finded) {
			if(!curr.has_extension())
				build_Tree(finded, path);
			else {
				ntNode* newNode = new ntNode;
				fs::path curr1 = path;
				newNode->key = curr1.filename().generic_string();
				newNode->path = curr1.generic_string();
				newNode->childs = new vector<ntNode*>;
				finded->childs->push_back(newNode);
				fileTree->Insert(newNode->key, newNode->path);
			}
		}
		else{
			cout << "Path Where you want to insert doesn't found" << endl;
		}
	}
	void remove(string What) {
		ntNode* finded = find(What);
		fs::path curr = What;
		if (finded) {
			if (curr.has_extension()) {
				fileTree->remove(curr.filename().generic_string(), curr.generic_string());
				ntNode* findParent = find(curr.parent_path().generic_string());
				int i = 0;
				for (vector<ntNode*> ::iterator it = findParent->childs->begin(); it != findParent->childs->end(); ++it,++i){
					if ((*it)->path == What) {
						findParent->childs->erase(findParent->childs->begin() + i);
						break;
					}
				}
			}
			else {
				ntNode* findParent = find(curr.parent_path().generic_string());
				int i = 0;
				//queue<string>* fileTodelete = new queue<string>;
				queue<ntNode*> myqueue;
				for (vector<ntNode*> ::iterator it = finded->childs->begin(); it != finded->childs->end(); ++it)
					myqueue.push(*(it));
				while (!myqueue.empty()) {
					ntNode* top = myqueue.front();
					myqueue.pop();
					fileTree->remove(top->key, top->path);
					for (vector<ntNode*> ::iterator it = top->childs->begin(); it != top->childs->end(); ++it)
						myqueue.push(*(it));
				}
				for (vector<ntNode*> ::iterator it = findParent->childs->begin(); it != findParent->childs->end(); ++it, ++i) {
					if ((*it)->path == What) {
						findParent->childs->erase(findParent->childs->begin() + i);
						break;
					}
				}
			}
		}
	}
	
	ntNode* find(string key) {
		if (root->path == key) {
			return root;
		}
		else{
			queue<ntNode*> myqueue;
			for (vector<ntNode*> ::iterator it = root->childs->begin(); it != root->childs->end(); ++it)
				myqueue.push(*(it));
			while (!myqueue.empty()) {
				ntNode* top = myqueue.front();
				if (top->path == key)
					return top;
				else{
					for (vector<ntNode*> ::iterator it = top->childs->begin(); it != top->childs->end(); ++it)
						myqueue.push(*(it));
				}
				myqueue.pop();
			}
			return NULL;
		}
	}
	void merge(string path1, string path2) {
		fs::path path_1 = path1;
		fs::path path_2 = path2;
		ntNode* node1=find(path_1.generic_string());
		ntNode* node2=find(path_2.generic_string());
		cout << node1->path << endl;
		if (node1 && node2) {
			ntNode* node1_parent = find(path_1.parent_path().generic_string());
			ntNode* node2_parent = find(path_2.parent_path().generic_string());
			int i = 0;
			for (vector<ntNode*>::iterator it = node2->childs->begin(); it != node2->childs->end(); ++i,++it) {
				node1->childs->push_back(*it);
			}
			i = 0;
			for (vector<ntNode*>::iterator it = node2_parent->childs->begin(); it != node2_parent->childs->end(); ++i,++it) {
				if ((*it)->key == node2->key) {
					node2_parent->childs->erase(node2_parent->childs->begin() + i);
					break;
				}
			}
		}
		else {
			cout << "Path is incorrent" << endl;
		}

	}
	void display_in_Order() {
		inOrder(root);
	}
	QuickSearchTree*& getfileTree() {
		return fileTree;
	}
	void display_pre_Order() {
		preOrder(root);
	}
	void display_post_Order() {
		postOrder(root);
	}
	void display_level_Order() {
		levelOrder(root);
	}
	int SizeOfDirectory(string path) {
		int sumOfSizeOfFile = 0;
		fs::path p = path;
		if (p.has_extension()) {
			return (int)fs::file_size(p);
		}
		else {
			for (auto& currPath : fs::recursive_directory_iterator(path)) {
				fs::path curr = currPath;
				if (curr.has_extension()) {
					sumOfSizeOfFile += (int)fs::file_size(curr);
				}
			}
		}
		return sumOfSizeOfFile;
	}
	~nTree() {
		if (root) {
			delete root;
		}
		if (fileTree) {
			delete fileTree;
		}

	}
};