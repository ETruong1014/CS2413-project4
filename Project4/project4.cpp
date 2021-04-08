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
	BinarySearchTree<int>* bst = new BinarySearchTree<int>();

	while (!cin.eof()) {
		cin >> operation; //read operation
		cout << operation << endl;
		switch(operation) {
		case 'I': //insert a coordinate
			cin >> val1 >> val2 >> val3;
			try {
				(*bst).insert(val1, val2, val3);
			}
			catch (BinarySearchTreeChangedSubtree e){
				cout << "Cannot directly access subtree" << endl;
			}
			break;
		case 'R': //remove a coordinate
			cin >> val1 >> val2;
			try {
				(*bst).remove(val1, val2);
			}
			catch (BinarySearchTreeChangedSubtree e){
				cout << "Cannot directly access subtree" << endl;
			}
			catch (BinarySearchTreeNotFound e) {
				cout << "Point not found" << endl;
			}
			break;
		case 'F': //find a coordinate
			cin >> val1 >> val2;
			try {
				cout << (*bst).find(val1, val2) << endl; //print out identifier of coordinate
			}
			catch (BinarySearchTreeNotFound e) {
				cout << "Point not found" << endl;
			}
			break;
		case 'S': //search for values in a range
			cin >> val1 >> val2 >> val3 >> val4;
			(*bst).rangeSearch(val1, val2, val3, val4);
			break;
		case 'Y': //balance a y-tree
			cin >> val1;
			try {
				(*bst).yRebalance(val1); //rebalance the y-tree at given x-value
			}
			catch (BinarySearchTreeChangedSubtree e){
				cout << "Cannot directly access subtree" << endl;
			}
			catch (BinarySearchTreeNotFound e) {
				cout << "x value not found" << endl;
			}
			break;
		case 'X': //balance the x-tree
			try {
				bst = (*bst).xRebalance(); //rebalance the x-tree and reassign root node
			}
			catch (BinarySearchTreeChangedSubtree e){
				cout << "Cannot directly access subtree" << endl;
			}
			break;
		case 'P': //print the x-tree and each x-node's y-tree
			cout << "Test" << endl;
			break;
		}
	}
}


