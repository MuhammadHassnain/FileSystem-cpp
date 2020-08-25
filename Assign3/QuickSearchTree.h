#pragma once
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
struct File {
	string filename;
	string path;
	File(string fn,string p) {
		filename = fn;
		path = p;
	}
	friend ostream& operator <<(ostream& out, const File& curr) {
		cout << curr.filename << endl;
		cout << curr.path << endl;
		return out;
	}
};
class qsNode {
public:
	char key;
	vector<File*>* data;
	qsNode* left;
	qsNode* right;
	qsNode() {
		key = '\0';
		data = NULL;//WRITE DESTRUCTOR FOR THIS
		left = right = NULL;
	}
	friend ostream& operator <<(ostream& out, const qsNode& curr) {
		cout << "Key:" << curr.key<<endl;
		for (vector<File*> ::iterator it = curr.data->begin(); it != curr.data->end(); ++it) {
			cout << *(*it)<<" ";
		}
		return out;
	}
	~qsNode() {
		
		if(data)delete data;
	}
};
class QuickSearchTree {
	qsNode* root;
	//inorder display in order
	void inOrder(qsNode* p) {
		if (p != NULL) {
			inOrder(p->left);
			cout << *p;
			inOrder(p->right);
		}
	}
	void postOrder(qsNode* p) {
		if (p != NULL) {
			postOrder(p->left);
			postOrder(p->right);
			cout << *p;
		}
	}
	void preOrder(qsNode* p) {
		if (p != NULL) {
			cout << *p;
			preOrder(p->left);
			preOrder(p->right);
		}
	}
	void levelOrder(qsNode* p) {
		cout << *p;
		queue<qsNode*> myqueue;
		myqueue.push(p->left);
		myqueue.push(p->right);
		while (!myqueue.empty()) {
			qsNode* top = myqueue.front();
			myqueue.pop();
			cout << *top;
			myqueue.push(top->left);
			myqueue.push(top->right);
		}
	}
	void makeDeletion(qsNode*& toDelete) {
		qsNode* tempNode;
		if (toDelete->right == NULL) {
			tempNode = toDelete;
			toDelete = toDelete->left;
			delete tempNode;
		}
		else if (toDelete->left == NULL) {
			tempNode = toDelete;
			toDelete = toDelete->right;
			delete tempNode;
		}
		else {
			tempNode = toDelete->right;
			while (tempNode->left)
				tempNode = tempNode->left;
			tempNode->left = toDelete->right;
			tempNode = toDelete;
			toDelete = toDelete->right;
			delete tempNode;
		}
	}
	void deleteNode(string fn, string p, qsNode*& nodePtr) {
		if (nodePtr == NULL) {
			cout << "Value not found" << endl;
			return;
		}
		else if (tolower(fn[0]) == nodePtr->key) {
			int i = 0;
			for (vector<File*>::iterator it = nodePtr->data->begin(); it != nodePtr->data->end(); ++it,++i) {
				if ((*it)->filename == fn && ((*it)->path == p)) {
					nodePtr->data->erase(nodePtr->data->begin() + i);
					if (nodePtr->data->size() == 0) {
						makeDeletion(nodePtr);
						break;
					}
					break;
				}
			}
		}
		else if (tolower(fn[0]) < nodePtr->key) {
			deleteNode(fn, p, nodePtr->left);
		}
		else if(tolower(fn[0])>nodePtr->key) {
			deleteNode(fn, p, nodePtr->right);
		}
	}
public:
	QuickSearchTree() {
		root = NULL;
	}
	void remove(string filename, string path) {
		deleteNode(filename, path, root);
	}
	void Insert(string fn, string path) {
		qsNode* nodePtr;
		qsNode* newNode = new qsNode;
		if (!root) {
			root = newNode;
			newNode->key = tolower(fn[0]);
			newNode->data = new vector<File*>;
			newNode->left = newNode->right = NULL;
			newNode->data->push_back(new File(fn, path));
		}
		else {
			nodePtr = root;
			while(nodePtr){
				if (tolower(fn[0]) < nodePtr->key) {
					if (nodePtr->left) {
						nodePtr = nodePtr->left;
					}
					else {
						nodePtr->left = newNode;
						newNode->key = tolower(fn[0]);
						newNode->data = new vector<File*>;
						newNode->left = newNode->right = NULL;
						newNode->data->push_back(new File(fn, path));
						break;
					}
				}
				else if (tolower(fn[0]) > nodePtr->key) {
					if (nodePtr->right) {
						nodePtr = nodePtr->right;
					}
					else {
						nodePtr->right = newNode;
						newNode->key = tolower(fn[0]);
						newNode->data = new vector<File*>;
						newNode->left = newNode->right = NULL;
						newNode->data->push_back(new File(fn, path));
						break;
					}
				}
				else {
					delete newNode;
					nodePtr->data->push_back(new File(fn, path));
					break;
				}
			}
		}
	}
	vector<File*>*& Find(string fn) {
		vector<File*>* founded = new vector<File*>;
		qsNode* curr = root;
		while (curr) {
			if (curr->key == tolower(fn[0])) {
				vector<File*>::iterator it = curr->data->begin();
				for (; it != curr->data->end(); ++it) {
					if ((*it)->filename == fn) {
						founded->push_back((*it));
					}
				}
				return founded;
			}
			else if (tolower(fn[0])<curr->key ) {
				curr = curr->left;
			}
			else {
				curr = curr->right;
			}
		}
		return founded;
	}
	void display_in_Order() {
		inOrder(root);
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
	~QuickSearchTree() {
		if(root)
			delete root;
	}
};
