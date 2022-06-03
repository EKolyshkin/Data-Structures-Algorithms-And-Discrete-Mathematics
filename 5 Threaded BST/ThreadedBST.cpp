 /*
 * Modified by Kye Nelson & Egor Kolyshkin on 12/11/2021.
 * Threaded Binary Search Tree and Node class.
 * 
 * Single threaded binary search tree. Each node points to inorder predecessor.
 * 
 * Constructors: default, parameterized constructor, vector constructor, copy.
 * Mutators: add, remove, sortVector
 * Accessors (Private): inorderTraverse, getDepth, getEntry, getSuccessor, leftMost
 * Accessors (Public): isEmpty, getDepth, getValues, getNumberOfNodes, contains
 */
#include <sstream>

#include "ThreadedBST.h"

using namespace std;
  
  // CONSTRUCTORS

// node constructor
Node::Node(int value, Node* left, Node* right, bool rightThread) : value{value}, left{left}, right{right}, rightThread{rightThread}
{
}

// default constructor
ThreadedBST::ThreadedBST() : rootPtr(nullptr)
{
}

// parameterized constructor
ThreadedBST::ThreadedBST(int value) : rootPtr(new Node(value))
{
}

// copy constructor
// creates a copy of another ThreadedBST class
ThreadedBST::ThreadedBST(const ThreadedBST &t)
{
  // sorts ThreadedBST as vector in preOrder form
  vector<int> values = t.getValues();
  vector<int> preOrder;
  sortVector(values, preOrder, 0, values.size()-1);
  // sets root of copy tree to first value in preOrder
  Node* root = new Node(preOrder[0]);
  rootPtr = root;
  root->value = preOrder[0];
  // adds rest of vector to copy tree.
  for(int i = 1; i < preOrder.size(); i++)
  {
    add(preOrder[i]);
  }
}

// destructor
ThreadedBST::~ThreadedBST()
{ 
  vector<int> values = getValues();
  for (int i = 0; i < values.size(); i++)
  {
    remove(values[i]);
  }
}

  // MUTATORS

// add integer value to tree
// returns true if added, false if there is a duplicate.
bool ThreadedBST::add(const int value)
{
  bool success;
  if (contains(value))
  { // can't add duplicate
    success = false;
  }
  else if (rootPtr == nullptr) 
  {
    Node* newNode = new Node(value);
    rootPtr = newNode;
    success = true;
  }
  else
  {
    Node* curPtr = rootPtr;
    Node* newNode = new Node(value); // node to add

    // reach a point without a fork
    while (curPtr->left != nullptr && curPtr->right != nullptr && !curPtr->rightThread)
    {
      if (value < curPtr->value)
      {
        curPtr = curPtr->left;
      }
      else
      {
        curPtr = curPtr->right;
      }
    }

    // we now may have left or right children only lol
    if (value < curPtr->value)
    { // if smaller, keep going left when one left child
      while (value < curPtr->value && curPtr->left != nullptr)
      {
        curPtr = curPtr->left;
      }
      if (value > curPtr->value)
      {
        while (value > curPtr->value && curPtr->right != nullptr && !curPtr->rightThread)
        {
          curPtr = curPtr->right;
        }
        if (value > curPtr->value)
        {
          newNode->rightThread = true;
          newNode->right = curPtr->right;
          curPtr->right = newNode;
          curPtr->rightThread = false;
        }
        else {
          newNode->rightThread = true;
          newNode->right = curPtr;
          curPtr->left = newNode;
        }
      }
      else 
      {
        curPtr->left = newNode;
        newNode->rightThread = true;
        newNode->right = curPtr;
      }
    }
    else
    { // if bigger, keep going right when one right child
      while (value > curPtr->value && curPtr->right != nullptr && !curPtr->rightThread)
      {
        curPtr = curPtr->right;
      }
      if (value > curPtr->value)
      {
        Node* successor = nullptr;

        if (curPtr->rightThread)
        {
          successor = curPtr->right;
        }

        curPtr->right = newNode;
        curPtr->rightThread = false;

        // creating thread
        newNode->rightThread = true;
        newNode->right = successor; 
      }
      else 
      {
        while(value < curPtr->value && curPtr->right != nullptr && !curPtr->rightThread)
        {
          curPtr = curPtr->left;
        }
        Node* successor = curPtr;
        curPtr->left = newNode;
        newNode->right = successor;
        newNode->rightThread = true;

      }

    }

    success = true;
  }
  
  return success;
}


// remove integer value from tree
// returns true if successfully removed, false if value not in tree.
bool ThreadedBST::remove(const int value)
{
  Node* removeNode = getEntry(value);

  if (removeNode == nullptr)
  { // if not found return false
    return false;
  }
  else
  {
    if (removeNode->left == nullptr && (removeNode->right == nullptr || removeNode->rightThread)) //if value is a leaf
    {
      Node* suc = getSuccessor(removeNode);
      if (removeNode == rootPtr) //if value is the last value in the tree
      {
        rootPtr->rightThread = false;
        rootPtr->left = nullptr;
        rootPtr->right = nullptr;
        delete rootPtr;
        rootPtr = nullptr;
      }
      else if (removeNode->right == suc) // if leaf is on the left
      {
        suc->left = nullptr;
        removeNode->left = nullptr;
        removeNode->right = nullptr;
        removeNode->rightThread = false;
        delete removeNode;
        removeNode = nullptr;
      }
      else //if leaf is on the right
      {
        suc->right = removeNode->right;
        suc->rightThread = true;
        removeNode->left = nullptr;
        removeNode->right = nullptr;
        removeNode->rightThread = false;
        delete removeNode;
        removeNode = nullptr;
      }

      return true;
    }

    if (removeNode->left != nullptr && removeNode->rightThread)//if value only has a left child
    {
      Node* suc = removeNode->right;
      Node* leftChild = removeNode->left;
      leftChild->right = suc;
      suc->left = leftChild;
      removeNode->left = nullptr;
      removeNode->right = nullptr;
      removeNode->rightThread = false;
      delete removeNode;
      removeNode = nullptr;
      return true;
    }

    if (removeNode->left == nullptr && removeNode->right != nullptr && !removeNode->rightThread)//if value only has a right child
    {
      Node* suc = getSuccessor(removeNode);
      Node* rightChild = removeNode->right;
      if (suc == nullptr)
      {
        rootPtr = removeNode->right;
      }
      else if (suc->value < removeNode->value)
      {
        suc->right = rightChild;
      }
      else {
        suc->left = rightChild;
      }
      removeNode->left = nullptr;
      removeNode->right = nullptr;
      removeNode->rightThread = false;
      delete removeNode;
      removeNode = nullptr;
      return true;
    }

    if (removeNode->left != nullptr && removeNode->right != nullptr && !removeNode->rightThread) //if value has two childs
    {
      Node* temp = leftMost(removeNode->right);
      int tempVal = temp->value;
      remove(temp->value);
      removeNode->value = tempVal;
      return true;
    }
  }

  return true;
}

// sorts a vector into preorder form to properly add to a balanced tree.
// returns true upon successful sort.
bool ThreadedBST::sortVector(vector<int> unsorted, vector<int>& sorted, int start, int end)
{
  int mid = (start + end) / 2; 

  if (start > end)
  {
    return false;
  }
  sorted.push_back(unsorted[mid]); 

  sortVector(unsorted, sorted, start, mid - 1); 
  sortVector(unsorted, sorted, mid + 1, end); 

  return true;
}


// overloaded out operator for printing
// calls inorderTraverse helper method.
ostream &operator<<(ostream &out, const ThreadedBST &tree)
{
  out << tree.inorderTraverse(tree.rootPtr);
  return out;
}

  // ACCESSORS

// check if empty
// returns true if empty, false if not.
bool ThreadedBST::isEmpty() const
{
  return rootPtr == nullptr;
}

// get Depth of tree
// returns depth of tree as an integer.
// calls getDepth(Node) helper method.
int ThreadedBST::getDepth() const
{
  return getDepth(rootPtr);
} 

// get Depth of tree (helper recursive method)
// returns ineger value of depth of tree.
int ThreadedBST::getDepth(const Node* curPtr) const
{
  if (curPtr == nullptr)
  { // if node doesn't exist
    return -1;
  }
  else if (curPtr->left == nullptr && (curPtr->rightThread || curPtr->right == nullptr))
  { // if node is leaf
    return 0;
  }
  else
  { // keep going down
    if (curPtr->rightThread)
    { // only left branch continues
      return 1 + getDepth(curPtr->left);
    }
    else
    { // both branches continue
      return 1 + max(getDepth(curPtr->left), getDepth(curPtr->right));
    }
  }
}

// get number of nodes in tree
// calls inorderTraverse method and returns integer value of number of nodes in tree.
int ThreadedBST::getNumberOfNodes() const
{
  int num = 0;
  string path = this->inorderTraverse(rootPtr);
  
  for (int i = 0; i < path.length(); i++)
  { // increments number of nodes for every space in traversal path
    if (path[i] == ' ')
    {
      num++;
    }
  }

  return num;
}

// checks if tree contains value
// returns true if value is in tree, false if not.
bool ThreadedBST::contains(const int value) const
{
  return getEntry(value) != nullptr;
}

// returns pointer to node with value in tree
Node* ThreadedBST::getEntry(const int value) const
{
  return getEntry(value, rootPtr);
}

// returns pointer to node with value in tree (helper recursive method)
Node* ThreadedBST::getEntry(const int value, Node* curPtr) const
{
  if (curPtr == nullptr)
  { // not found
    return nullptr;
  }
  else if (curPtr->value == value)
  { // found
    return curPtr;
  }
  else if (value < curPtr->value)
  { // go left if smaller
    return getEntry(value, curPtr->left);
  }
  else
  { // go right if bigger
    if (!curPtr->rightThread)
    {
      return getEntry(value, curPtr->right);
    }
    else 
    {
      return nullptr;
    }
  }
}

// getter method to return successor node
// returns nullptr if successor not found.
Node* ThreadedBST::getSuccessor(const Node* curPtr)
{
  Node* temp = leftMost(rootPtr);
  //traverses tree from left inorder
  while (temp != nullptr)
  { // if temp's left or right children is curPtr, return temp.
    if (temp->left == curPtr || (temp->right == curPtr && !temp->rightThread))
    {
      return temp;
    }
    else 
    {
      if (temp->rightThread)
        temp = temp->right;
      else 
        temp = leftMost(temp->right);
    }
  }
  return nullptr;
}

// returns all the values in tree as a vector<int>
vector<int> ThreadedBST::getValues() const
{
  vector<int> values;
  Node* cur = leftMost(rootPtr);
  //traverses tree from left most node in order.
  while (cur != nullptr)
  {
    values.push_back(cur->value);
    if (cur->rightThread)
    {
      cur = cur->right;
    }
    else // Else go to the leftmost child in right subtree
    {
      cur = leftMost(cur->right);
    }
  }
  return values;

}

// Utility function to find leftmost node in a tree rooted with n
// returns a Node*
Node* ThreadedBST::leftMost(Node* root) const
{
  Node* n = root;
  if (n == nullptr)
  {
    return nullptr;
  }

  while (n->left != nullptr)
  {
    n = n->left;
  }

  return n;
}


// traverse tree inorder from leftmost of root.
// returns one string of the values.
string ThreadedBST::inorderTraverse(Node* root) const
{
  stringstream path;
  Node* cur = leftMost(root);

  while (cur != nullptr)
  {
    path << cur->value << " ";

    // If this node is a thread node, then go to
    // inorder successor
    if (cur->rightThread)
    {
      cur = cur->right;
    }
    else // Else go to the leftmost child in right subtree
    {
      cur = leftMost(cur->right);
    }
  }

  return path.str();
}  