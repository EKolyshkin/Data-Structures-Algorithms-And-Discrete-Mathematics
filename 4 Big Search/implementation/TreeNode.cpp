/* Created by Egor Kolyshkin on 02/08/2022 */

#include "TreeNode.h"

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

// parameterized constructor
TreeNode::TreeNode(bool isLeaf) : isLeaf{isLeaf}
{
   size = 0;
   keys.resize(3);
   values.resize(3);
   children.resize(4);
}

// destructor
TreeNode::~TreeNode() {}

// Helper function to print node inorder recursively
void TreeNode::inOrderVisit(function<void(shared_ptr<string>, int)> visit) const
{
   int i; // i keys, values, and i + 1 children
   for (i = 0; i < size; i++)
   {
      if (!isLeaf)
      { // traverse subtree, then print keys and values
         children.at(i)->inOrderVisit(visit);
      }
      // print key and its value
      visit(keys.at(i), values.at(i));
   }

   if (!isLeaf)
   { // print rightmost child subtree
      children.at(i)->inOrderVisit(visit);
   }
}

// Helper search finds index to which key and value are associated
int TreeNode::findIndex(shared_ptr<string> key) const
{
   int i = 0;
   while (i < size && compare(keys.at(i), key) == -1)
   { // find index equal or larger than key
      i++;
   }

   return i;
}

// Compare two string pointers -1 if left less, 1 if right less, 0 if equal
int TreeNode::compare(shared_ptr<string> left, shared_ptr<string> right) const
{
   for (unsigned int i = 0; i < left->length() && i < right->length(); i++)
   { // compare maxmium amount of chars in both strings
      if (left->at(i) < right->at(i))
      { // if left char comes before right
         return -1;
      }
      else if (left->at(i) > right->at(i))
      { // if right char comes before left char
         return 1;
      }
   }
   // all comparable chars are the same
   if (left->length() < right->length())
   { // if left has less chars
      return -1;
   }
   else if (left->length() > right->length())
   { // if right has less chars
      return 1;
   }
   else
   { // if both have same chars
      return 0;
   }
}

// Helper Insert a key in subtree of semi-full node
void TreeNode::insertSemi(shared_ptr<string> key, int value)
{
   int i = size - 1; // start from rightmost key

   if (isLeaf == true)
   { // if this is a leaf, insert key before next bigger key
      while (i >= 0 && compare(keys.at(i), key) == 1)
      { // move all keys bigger to the right and decrease index
         keys.at(i + 1) = keys.at(i);
         values.at(i + 1) = values.at(i);
         i--;
      }
      // replace duplicate key at index with new key
      keys.at(i + 1) = key;
      values.at(i + 1) = value;
      size += 1;
   }
   else
   { // if not isLeaf, insert key into child
      while (i >= 0 && compare(keys.at(i), key) == 1)
      {
         i--;
      }

      if (children.at(i + 1)->size == 3)
      { // if found child is full, split it
         split(i + 1, children.at(i + 1));

         if (compare(keys.at(i + 1), key) == -1)
         { // find which split child to insert the key into
            i++;
         }
      }

      children.at(i + 1)->insertSemi(key, value);
   }
}

// Helper Insert split full child childPtr with index index in vector children
void TreeNode::split(int index, shared_ptr<TreeNode> childPtr)
{ // node newRoot will store 1 less keys of childPtr
   shared_ptr<TreeNode> newRoot = make_shared<TreeNode>(TreeNode(childPtr->isLeaf));
   newRoot->size = 1;

   for (int i = 0; i < 1; i++)
   { // copy 1 less keys from childPtr to newRoot
      newRoot->keys.at(i) = childPtr->keys.at(i + 2);
      newRoot->values.at(i) = childPtr->values.at(i + 2);
   }

   if (!childPtr->isLeaf)
   { // if new child being split has children
      for (int i = 0; i < 2; i++)
      { // copy all children from childPtr to newRoot
         newRoot->children.at(i) = childPtr->children.at(i + 2);
      }
   }

   childPtr->size = 1;

   for (int i = size; i >= index + 1; i--)
   { // move child pointers to make space for new child
      children.at(i + 1) = children.at(i);
   }

   // newRoot is now a child of this node
   children.at(index + 1) = newRoot;

   for (int i = size - 1; i >= index; i--)
   { // find index of new key and move all bigger keys
      keys.at(i + 1) = keys.at(i);
      values.at(i + 1) = values.at(i);
   }

   // middle key of childPtr is now in this node
   keys.at(index) = childPtr->keys.at(1);
   values.at(index) = childPtr->values.at(1);
   size += 1;
}

// Helper remove function for index key
void TreeNode::remove(shared_ptr<string> key)
{
   int i = findIndex(key);

   if (i < size && compare(key, keys.at(i)) == 0)
   { // if key exists in this node
      if (isLeaf)
      { // remove key from leaf node
         removeLeaf(i);
      }
      else
      { // remove key from middle node
         removeMiddle(i);
      }
   }
   else if (!isLeaf)
   { // if key does not exist and this is not a isLeaf node
      bool flag = false;
      if (i == size)
      {
         flag = true;
      }

      if (children.at(i)->size < 2)
      { // fill child if it has too few keys
         fill(i);
      }

      if (flag && i > size)
      { // rightmost child added to previous child
         children.at(i - 1)->remove(key);
      }
      else
      { // rightmost child has not been added
         children.at(i)->remove(key);
      }
   }
}

// Helper remove key at index from isLeaf node
void TreeNode::removeLeaf(int index)
{
   for (int i = index + 1; i < size; i++)
   { // move all keys one left
      keys.at(i - 1) = keys.at(i);
      values.at(i - 1) = values.at(i);
   }

   size--;
}

// Helper remove key at index from middle node
void TreeNode::removeMiddle(int index)
{
   shared_ptr<string> key = keys.at(index);
   // if child has max keys
   if (children.at(index)->size >= 2)
   { // replace index with previous
      int prevValue;
      shared_ptr<string> prev = getPrev(index, prevValue);
      keys.at(index) = prev;
      values.at(index) = prevValue;
      // continue removing prev children
      children.at(index)->remove(prev);
   }
   // if next child has max keys
   else if (children.at(index + 1)->size >= 2)
   { // replace index with next
      int nextValue;
      shared_ptr<string> next = getNext(index, nextValue);
      keys.at(index) = next;
      values.at(index) = nextValue;
      // continue removing next children
      children.at(index + 1)->remove(next);
   }
   // if both children have max keys
   else
   { // merge children from next to current index
      merge(index);
      // continue removing key children
      children.at(index)->remove(key);
   }
}

// get previous index to key parent
shared_ptr<string> TreeNode::getPrev(int index, int &value)
{
   shared_ptr<TreeNode> curPtr = children.at(index);

   while (!curPtr->isLeaf)
   { // find rightmost node that is a leaf
      curPtr = curPtr->children.at(curPtr->size);
   }
   // return last key of rightmost leaf node
   value = curPtr->values.at(curPtr->size - 1);
   return curPtr->keys.at(curPtr->size - 1);
}

// get next index to key parent
shared_ptr<string> TreeNode::getNext(int index, int &value)
{
   shared_ptr<TreeNode> curPtr = children.at(index + 1);

   while (!curPtr->isLeaf)
   { // find leftmost node that is a leaf
      curPtr = curPtr->children.at(0);
   }
   // return first key of leftmost leaf node
   value = curPtr->values.at(0);
   return curPtr->keys.at(0);
}

// fill child node at index
void TreeNode::fill(int index)
{
   if (index != 0 && children.at(index - 1)->size >= 2)
   { // borrow previous key from left of index
      borrowPrev(index);
   }
   else if (index != size && children.at(index + 1)->size >= 2)
   { // borrow next key from right of index
      borrowNext(index);
   }
   else
   { // merge child with sibling
      if (index != size)
      { // merge with previous sibling
         merge(index);
      }
      else
      { // merge with next sibling
         merge(index - 1);
      }
   }
}

// move previous child to current index
void TreeNode::borrowPrev(int index)
{
   shared_ptr<TreeNode> child = children.at(index);
   shared_ptr<TreeNode> sibling = children.at(index - 1);

   // sibling will lose one key and child will gain one
   for (int i = child->size - 1; i >= 0; i--)
   { // move all keys forward one
      child->keys.at(i + 1) = child->keys.at(i);
      child->values.at(i + 1) = child->values.at(i);
   }

   if (!child->isLeaf)
   { // if child is not a leaf
      for (int i = child->size; i >= 0; i--)
      { // move all children forward one
         child->children.at(i + 1) = child->children.at(i);
      }
   }
   // first key of child will be left of current key index
   child->keys.at(0) = keys.at(index - 1);
   child->values.at(0) = values.at(index - 1);

   if (!child->isLeaf)
   { // move last child of sibling to first child of index child
      child->children.at(0) = sibling->children.at(sibling->size);
   }
   // move key from sibling to parent
   keys.at(index - 1) = sibling->keys.at(sibling->size - 1);
   values.at(index - 1) = sibling->values.at(sibling->size - 1);

   child->size += 1;
   sibling->size -= 1;
}

// move next child to current index
void TreeNode::borrowNext(int index)
{
   shared_ptr<TreeNode> child = children.at(index);
   shared_ptr<TreeNode> sibling = children.at(index + 1);

   // last key in child will be key index
   child->keys.at(child->size) = keys.at(index);
   child->values.at(child->size) = values.at(index);

   if (!child->isLeaf)
   { // first child of sibling will be last child of child
      child->children.at(child->size + 1) = sibling->children.at(0);
   }

   // first key of sibling will be this key index
   keys.at(index) = sibling->keys.at(0);
   values.at(index) = sibling->values.at(0);

   for (int i = 1; i < sibling->size; i++)
   { // move all keys backward one
      sibling->keys.at(i - 1) = sibling->keys.at(i);
      sibling->values.at(i - 1) = sibling->values.at(i);
   }

   if (!sibling->isLeaf)
   { // move all children backward one
      for (int i = 1; i <= sibling->size; i++)
      {
         sibling->children.at(i - 1) = sibling->children.at(i);
      }
   }

   child->size += 1;
   sibling->size -= 1;
}

// merge two children at index and index + 1
void TreeNode::merge(int index)
{
   shared_ptr<TreeNode> child = children.at(index);
   shared_ptr<TreeNode> sibling = children.at(index + 1);

   // last key of child is key index of this node
   child->keys.at(1) = keys.at(index);
   child->values.at(1) = values.at(index);

   for (int i = 0; i < sibling->size; i++)
   { // move keys from sibling to child
      child->keys.at(i + 2) = sibling->keys.at(i);
      child->values.at(i + 2) = sibling->values.at(i);
   }

   if (!child->isLeaf)
   { // move child pointers from sibling to child
      for (int i = 0; i <= sibling->size; i++)
      {
         child->children.at(i + 2) = sibling->children.at(i);
      }
   }

   for (int i = index + 1; i < size; i++)
   { // move all keys backward one
      keys.at(i - 1) = keys.at(i);
      values.at(i - 1) = values.at(i);
   }
   for (int i = index + 2; i <= size; i++)
   { // move all children backward one
      children.at(i - 1) = children.at(i);
   }

   child->size += sibling->size + 1;
   size--;
}