#ifndef THREADEDBST_H
#define THREADEDBST_H

#include <iostream>
#include <vector>
#include <array>

using namespace std;

struct Node
{
public:
  // FIELDS
  int value; // value of node
  Node* left; // left pointer
  Node* right; // right pointer  
  bool rightThread; // inorder successor

  // CONSTRUCTORS
  explicit Node(int value, Node* left = nullptr, Node* right = nullptr, bool rightThread = false); // constructor
};

class ThreadedBST
{
  friend ostream &operator<<(ostream &out, const ThreadedBST &tree); // overloaded out operator for printing

private:
  // FIELDS
  Node* rootPtr; // pointer to root of tree

  // ACCESSORS
  string inorderTraverse(Node* root) const;   // traverse inorder
  int getDepth(const Node* curPtr) const; // get depth of tree (helper recursive method)
  Node* getEntry(const int value) const; // returns pointer to node with value in tree
  Node* getEntry(const int value, Node* curPtr) const; // returns pointer to node with value in tree (helper recursive method) 
  Node* getSuccessor(const Node* cur); //returns successor of node
  Node* leftMost(Node* root) const; //returns left most node of root

public:
  // CONSTRUCTORS
  ThreadedBST(); // default constructor
  explicit ThreadedBST(int value); // constructor
  ThreadedBST(const vector<int> &values); // creates new tree with all values in vector
  ThreadedBST(const ThreadedBST &t); // copy constructor
  virtual ~ThreadedBST(); // destructor

  // MUTATORS
  bool add(const int value); // add value to tree
  bool sortVector(const vector<int> unsorted, vector<int>& sorted, int start, int end);
  bool remove(const int value); // remove value from tree
  
  // ACCESSORS
  bool isEmpty() const; // check if empty
  int getDepth() const; // get depth of tree
  vector<int> getValues() const;
  int getNumberOfNodes() const; // get number of nodes in tree
  bool contains(int value) const; // checks if tree contains value
};

#endif // THREADEDBST_H