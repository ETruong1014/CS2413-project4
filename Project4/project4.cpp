/*
 * project4.cpp
 *
 *  Created on: Apr 3, 2021
 *      Author: erictruong1014
 */

#include "BinarySearchTree.h"
#include<iostream>

using namespace std;

int main()
{
    char operation; //letter for the operation
	int val1;
	int val2;
	int val3;
	int val4;
	BinarySearchTree<int>* bst = new BinarySearchTree<int>(); //pointer to root of x-tree

	while (cin >> operation) { //read until end of file, when operation assignment fails
		switch(operation) {
		case 'I': //insert a coordinate
			cin >> val1 >> val2 >> val3;
			(*bst).insert(val1, val2, val3); //insertion
			cout << val1 << " " << val2 << " " << val3 << endl; //print out values inserted
			break;
		case 'R': //remove a coordinate
			cin >> val1 >> val2;
			cout << "Remove: " << val1 << " " << val2 << endl; //print out coordinate to remove
			try {
				(*bst).remove(val1, val2); //removal
			}
			catch (BinarySearchTreeNotFound e) {
				cout << "The element you are trying to remove is not in the tree " << endl;
			}
			break;
		case 'F': //find a coordinate
			cin >> val1 >> val2;
			cout << "Find: " << val1 << " " << val2 << endl;
			(*bst).find(val1, val2); //print out coordinate and identifier
			break;
		case 'S': //search for values in a range
			cin >> val1 >> val2 >> val3 >> val4;
			cout << "Range search " << endl;
			cout << val1 << " " << val2 << " " << val3 << " " << val4 << endl; //print out range
			(*bst).rangeSearch(val1, val2, val3, val4); //print values in the range
			break;
		case 'Y': //balance a y-tree
			cin >> val1;
			cout << "Y tree balance" << endl;
			cout << val1 << endl;
			try {
				(*bst).yRebalance(val1); //rebalance the y-tree at given x-value
			}
			catch (BinarySearchTreeNotFound e) {
				cout << "X value not found" << endl;
			}
			break;
		case 'P': //print the x-tree and each x-node's y-tree
			cout << "Print" << endl;
			cout << "INORDER TRAVERSAL: " << endl;
			(*bst).printInorder(); //print inorder traversal
			cout << "PREORDER TRAVERSAL: " << endl;
			(*bst).printPreorder(); //print preorder traversal
			cout << endl;
			break;
		}
	}
}


