// Assign3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<filesystem>
#include"nTree.h"
namespace fs = std::experimental::filesystem;
using namespace std;


int main() {
	bool loop;
	string temp1, temp2;
	vector<File*>* finded;
	int orderChoice;
	fs::path path = "D:/My Data/Study/Fall2017/Data Structure/Assignment/Assignment3/logs";
	nTree directory(path.generic_string());
	QuickSearchTree* fileTree = directory.getfileTree();
	do {
		int choice;
		cout << "Press 1. To view File Directory in Different Order.\nPress 2. To Search a specific log file\nPress 3. To Merge two Directories"
			"\nPress 4. To add a log file/directory\nPress 5. To Delete a log file/directory\nPress 6. To View Size of directory/log file\n>>>";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Press 1. For Pre-Order\nPress 2. For Post-Order\nPress 3. For In-Order\nPress 4. For Tree Order\nPress 5. For Level Order\n>>>";
			cin >> orderChoice;
			if (orderChoice == 1) {
				directory.display_pre_Order();
			}
			else if (orderChoice == 2) {
				directory.display_post_Order();
			}
			else if (orderChoice == 3 || orderChoice == 4) {
				directory.display_in_Order();
			}
			else if (orderChoice == 5) {
				directory.display_level_Order();
			}
			else {
				cout << "Wrong Choice" << endl;
			}
			break;
		case 2:
			cout << "Enter Log file Name";
			cin >> temp1;
			finded= fileTree->Find(temp1);
			if (finded) {
				vector<File*>::iterator it = finded->begin();
				for (; it != finded->end(); ++it) {
					cout << *(*it) << endl;
				}
			}
			break;
		case 3:
			cout << "Enter address of directory 1:";
			cin.ignore();
			getline(cin, temp1);
			cout << "Enter address of directory 2:";
			getline(cin, temp2);
			directory.merge(temp1, temp2);
			break;
		case 4:
			cout << "Enter address of file or folder which you want to insert:";
			cin.ignore();
			getline(cin, temp1);
			cout << "Enter address of folder where you want to insert:";
			getline(cin, temp2);
			directory.insert(temp2, temp1);
			break;
		case 5:
			cout << "Enter address of file or folder which you want to delete:";
			cin.ignore();
			getline(cin, temp1);
			directory.remove(temp1);
			break;
		case 6:
			cout << "Enter address of file or folder to calculate it's size:";
			cin.ignore();
			getline(cin, temp1);
			cout << "Size of Directory " << path << " is:" << directory.SizeOfDirectory(temp1) << endl;
			break;
		default:
			cout << "Wrong Choice" << endl;


		}
		cout << "Enter 1 to continue";
		cin >> loop;
		system("CLS");
	} while (loop);
	system("pause");
	return 0;
}

