/*
 *    Data Structures Featuring C++  (c) 2021 Sridhar Radhakrishnan
 */

#include <iostream>
using namespace std;

#ifndef __BINARYSEARCHTREE__H
#define __BINARYSEARCHTREE__H

#include <cstdlib>


int max (int a, int b)
{
	if (a < b) return b;
	else return a;
}

class Exception {};

class BinaryTreeException : Exception {};
class BinaryTreeMemory : BinaryTreeException {}; //memory issue
class BinaryTreeEmptyTree : BinaryTreeException {}; //empty tree encountered

class BinarySearchTreeException: BinaryTreeException {};
class BinarySearchTreeChangedSubtree : BinarySearchTreeException {}; //attempting to directly access a subtree
class BinarySearchTreeNotFound : BinarySearchTreeException {}; //value not found

template <class DataType>
class BinarySearchTree;

template <class DataType>
ostream& operator << (ostream& s,  BinarySearchTree<DataType>& X);

// /////////////////////////////////////////////////////////////
template <class DataType>
class BinarySearchTree
// /////////////////////////////////////////////////////////////
{
	friend ostream& operator<< <DataType> (ostream& s,  BinarySearchTree<DataType>& X);
protected:
	DataType* _root; //root of the tree
	int _ID; //ID number of a y-node, 0 if it is an x-node
	BinarySearchTree<DataType>* _left; //left node of the tree
	BinarySearchTree<DataType>* _right; //right node of the tree
	BinarySearchTree<DataType>* _yTree; //pointer to the root of the x-node's y-tree
	bool _subtree; //true if tree node is a subtree
	virtual BinarySearchTree<DataType>* makeSubtree(); //create a subtree
	virtual void copyTree (BinarySearchTree<DataType>* bst); //copy a tree
	virtual void _makeNull (); //make a tree node NULL
	BinarySearchTree<DataType>* _find (const DataType& data); //find a node in the tree containing the value
public:
	BinarySearchTree (); //default constructor
	BinarySearchTree (const DataType& data); //non-default constructor
	virtual ~BinarySearchTree (); //destructor
	virtual bool isEmpty();
    // returns true if tree is empty,
    // but otherwise returns false
	virtual int height ();
    // returns the height (or depth) of the tree
	virtual int size ();
    // returns the number of nodes in the tree
	virtual DataType& root ();
    // returns data from the root
	virtual BinarySearchTree<DataType>* left ();
    // returns the left subtree
	virtual BinarySearchTree<DataType>* right ();
    // returns the right subtree
	virtual bool subtree(); //returns true if tree is a subtree
	virtual void makeEmpty (); //make a tree empty
	virtual int find (const DataType& xVal, const DataType& yVal); //find a coordinate in the tree
	virtual void remove (const DataType& xData, const DataType& yData); //remove a coordinate from the tree
	virtual void rangeSearch (const DataType& xLow, const DataType& xHigh, const DataType& yLow, const DataType& yHigh); //search for values in a range
	virtual void insert (const DataType& xData, const DataType& yData, int id); //insert a coordinate into the tree
	virtual BinarySearchTree<DataType>* globalRebalance(BinarySearchTree<DataType>* arr, int left, int right); //global rebalance method to rebalance the tree
};
template <class DataType>
ostream& operator<< (ostream& s,  BinarySearchTree<DataType>& X) {

	if (!X.isEmpty()) { //if the tree is not empty
		s << *(X.left ()) << " " << X.root () << " " << *(X.right()); //prints contents of the tree
	}
	return s;
}

// ==============================================================
template <class DataType>
BinarySearchTree<DataType>::BinarySearchTree () //default constructor
{
	_root = NULL;
	_ID = 0;
	_left = NULL;
	_right = NULL;
	_yTree = NULL;
	_subtree = false;
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>::BinarySearchTree (const DataType& data) //non-default constructor
{
	_subtree = false;
	_root = new DataType(data);
	//if (data == NULL) throw BinaryTreeMemory();
	_left = makeSubtree ();
	_right = makeSubtree ();
	_yTree = new BinarySearchTree<DataType>(); //make a default y-tree root
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::makeSubtree() //make a subtree
{
	BinarySearchTree<DataType>* bst = new BinarySearchTree<DataType> (); //create a default node
	bst->_subtree = true; //new tree node is a subtree
	return bst;
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>::~BinarySearchTree () //destructor
{
	if (_root != NULL)
        delete _root;
    _root = NULL;
	if (_left != NULL)
        delete _left;
    _left = NULL;
	if (_right != NULL)
        delete _right;
    _right = NULL;
    if (_yTree != NULL)
    	delete _yTree;
    _ID = 0;
}
// --------------------------------------------------------------
template <class DataType>
bool BinarySearchTree<DataType>::isEmpty()
{
	return (_root == NULL); //return true if root is NULL, object is empty
}
// --------------------------------------------------------------
template <class DataType>
int BinarySearchTree<DataType>::height ()
{
	if (isEmpty()) return 0;
    return (1 + max (_left->height(), _right->height())); //returns 1 + the higher number of the height of the left or right subtrees
   	// max() is in stdlib.h
}
// --------------------------------------------------------------
template <class DataType>
int BinarySearchTree<DataType>::size ()
// returns the number of nodes in the tree
{
	if (isEmpty())
		return 0;
	return (1 + _left->size() + _right->size()); //returns 1 + the numebr of nodes in the left and right subtrees
}
// --------------------------------------------------------------
template <class DataType>
DataType& BinarySearchTree<DataType>::root ()
{
	if (isEmpty()) throw BinaryTreeEmptyTree();
	return *_root;
}
// returns data from the root
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::left () { return _left; }
// returns the left subtree
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::right (){ return _right; }
// returns the right subtree
// --------------------------------------------------------------
template <class DataType>
bool BinarySearchTree<DataType>::subtree() { return _subtree; }
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::makeEmpty ()
{
	if (_subtree) throw BinarySearchTreeChangedSubtree(); //exception thrown if attempting to directly access a subtree
	if (_root != NULL)
   		delete _root;
    _root = NULL;
	if (_left != NULL)
	   	delete _left;
    _left = NULL;
	if (_right != NULL)
	   	delete _right;
    _right = NULL;
    if (_yTree != NULL)
    	delete _yTree;
    _yTree = NULL;
    _ID = 0;
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::copyTree(BinarySearchTree<DataType>* bst) //copy a tree
{
	_root = bst->_root;
	_left = bst->_left;
	_right = bst->_right;
	_yTree = bst->_yTree;
	_ID = bst->_ID;
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::_makeNull () //make a tree node NULL
{
	_root = NULL;
	_left = NULL;
	_right = NULL;
	_yTree = NULL;
	_ID = 0;
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::_find (const DataType& data) //finds node in the tree containing the value
{
	BinarySearchTree<DataType>* bst = this; //creates a pointer to the root node
	while (true)
	{
		if (bst->isEmpty()) //if the node is empty
			return bst; //return pointer to the current node
		if (*(bst->_root) < data) //if the value in the current node is less than the value to search for
		{
			bst = bst->_right; //search right subtree
		}
		else if (*(bst->_root) > data) //if the value in the current node is greater than the value to search for
		{
            bst = bst->_left; //search left subtree
		}
		else //value found
		{
			return bst; //return pointer to current node
		}
	}
}
// --------------------------------------------------------------
template <class DataType>
int BinarySearchTree<DataType>::find (const DataType& xVal, const DataType& yVal) //find a coordinate in the tree
{
	BinarySearchTree<DataType>* xBST = _find (xVal); //pointer to the x-node that may contain the x-value
	try{
		if (xBST->isEmpty()) throw BinarySearchTreeNotFound(); //x-node is empty, value not found
	}
	catch(Exception e)
	{
		cout<<"\nSorry!!! Element is not found in the tree"<<endl;
		return 0;
	}
	
	BinarySearchTree<DataType>* yBST = _find (yVal); //pointer to the y-node that may contain the y-value
	try{
		if (yBST->isEmpty()) throw BinarySearchTreeNotFound(); //y-node is empty, value not found
		return yBST->_ID; //returns the identifier of the coordinate
	}
	catch(Exception e)
	{
		cout<<"\nSorry!!! Element is not found in the tree"<<endl;
		return 0;
	}
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::insert (const DataType& xData, const DataType& yData, int id) //insert a coordinate into the tree
{
	if (_subtree) throw BinarySearchTreeChangedSubtree(); //exception thrown if atttempting to directly access a subtree
	BinarySearchTree<DataType>* xBST = _find (xData); //find insertion point for x coordinate
	
	if (xBST->isEmpty()) //if empty node is found
	{
		xBST->_root = new DataType (xData);
		xBST->_left = makeSubtree ();
		xBST->_right = makeSubtree ();
	}
	else //same value found
	{
        delete xBST->_root;
		xBST->_root = new DataType (xData);
	}
	
	BinarySearchTree<DataType>* yBST = xBST->_yTree->_find (yData); //find insertion point for y coordinate
		
		if (yBST->isEmpty()) //if empty node is found
		{
			yBST->_root = new DataType (yData);
			yBST->_ID = id;
			yBST->_left = makeSubtree ();
			yBST->_right = makeSubtree ();
		}
		else //same value found
		{
	        delete yBST->_root;
			yBST->_root = new DataType (yData);
			yBST->_ID = id;
		}
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::remove (const DataType& xData, const DataType& yData) //remove a coordinate from the tree
{
	if (_subtree) throw BinarySearchTreeChangedSubtree(); //exception thrown if attempting to directly access a subtree
	BinarySearchTree<DataType>* xBST;
	BinarySearchTree<DataType>* yBST;
	BinarySearchTree<DataType>* bst2;
	BinarySearchTree<DataType>* bst3;

	xBST = _find (xData); //find x-node in the tree
	if (xBST->isEmpty()) throw BinarySearchTreeNotFound(); //exception thrown if x-node not found
	yBST = xBST->_yTree->_find (yData); //find y-node in the tree
	if (yBST->isEmpty()) throw BinarySearchTreeNotFound(); //exception thrown if x-node not found

    // dispose of the existing data; the pointer will be overwritten
    delete yBST->_root;

    // .............................................................
	if (yBST->_left->isEmpty())
	{
        // the left subtree exists, but the pointer will be overwritten,
        // so we must dispose of it
        delete yBST->_left;
        bst2 = yBST->_right;		// save the pointer to the right subtree
		yBST->copyTree (bst2);	// copy the right subtree;
        // this empties tree if right empty
        bst2->_makeNull ();		// prepare right subtree for deletion
        delete bst2;				// delete right subtree to avoid garbage
	}

	else if (yBST->_right->isEmpty())
	{
        // the right subtree exists, but the pointer will be overwritten,
        // so we must dispose of it
        delete yBST->_right;
        bst2 = yBST->_left;		// save the pointer to the left subtree
		yBST->copyTree (bst2);	// copy the left subtree
        bst2->_makeNull ();		// prepare left subtree for deletion
        delete bst2;				// delete left subtree to avoid garbage
	}

	else		// both subtrees non-empty
	{
        // move to the right
		bst2 = yBST->_right;
        // then move down to the left as far as possible
		while (!bst2->_left->isEmpty()) bst2 = bst2->_left;
        // overwrite the data pointer
		yBST->_root = bst2->_root;

        // bst2's left child is known to be empty and pointer will be overwritten
     	delete bst2->_left;
        // now bst2's right child is copied into it
		if (bst2->_right->isEmpty()) //if bst2's right child is empty, simply delete it
        {
	     	delete bst2->_right;
            bst2->_makeNull();
        }
		else //if bst2's right child exists
        {
            bst3 = bst2->_right; //save the pointer to bst2's right child
            bst2->copyTree(bst2->_right); //copy bst2's right child into itself
            bst3->_makeNull (); //prepare bst2's right subtree for deletion
            delete bst3; //delete bst2's right subtree
        }
	}
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::rangeSearch (const DataType& xLow, const DataType& xHigh, const DataType& yLow, const DataType& yHigh) //search for values in a range
{
	if (isEmpty()) return;
	if (_ID == 0 && _yTree != NULL) { //if current node is an x-node
		if (*_root >= xLow) //if x-value is still higher than or equal to the x-low
		{
		    _left->rangeSearch(xLow, xHigh, yLow, yHigh); //search in left x-subtree as well
		    if (*_root <= xHigh) //if x-value is also less than or equal to the x-high
			{
				_yTree->rangeSearch(xLow, xHigh, yLow, yHigh); //start range search for y-tree
			}
		}
		if (*_root <= xHigh) //if x-value is still less than or equal to the x-high
		    _right->rangeSearch(xLow, xHigh, yLow, yHigh); //search in the right x-subtree as well
	}
	else if (_ID != 0 && _yTree == NULL) { //if current node is a y-node
		if (*_root >= yLow) //if y-value is still higher than or equal to the y-low
		{
			_left->rangeSearch(xLow, xHigh, yLow, yHigh); //search in left y-subtree as well
			if (*_root <= yHigh) //if y-value is also less than or equal to the y-high
			{
				cout << _ID << " "; //print out the identifier
			}
		}
		if (*_root <= yHigh) //if y-value is still less than or equal to the y-high
			_right->rangeSearch(xLow, xHigh, yLow, yHigh); //search in the right y-subtree as well
	}
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::globalRebalance(BinarySearchTree<DataType>* arr, int left, int right) { //global rebalance method to balance the tree
	
	int mid = 0; //mid index of the range
	BinarySearchTree<DataType>* temp = NULL; //temp storage for the pointer at mid
	
	if (left <= right) {
		mid = (left + right) / 2;
		temp = &arr[mid]; //store the pointer at mid
		(*temp)._left = globalRebalance(arr, left, mid - 1); //rebalance the left subtree
		(*temp)._right = globalRebalance(arr, mid + 1, right); //rebalance the right subtree
	}
	return temp;
}

#endif
