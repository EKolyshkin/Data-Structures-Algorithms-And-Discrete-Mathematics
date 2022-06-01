/* Created by Egor Kolyshkin on 02/08/2022 */

#include "Index.h"
#include "TreeNode.h"

#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <fstream>

// default constructor
Index::Index() : root{nullptr} {}

// destructor
Index::~Index() {}

/* Insert a key in the index, associate the integer value with the key
replace value of key if key already exists */
void Index::Insert(shared_ptr<string> key, int value)
{ // replace value if key exists and throw error if negative value
   if (replaceIfExists(key, value))
   {
      return;
   }
   // empty tree
   if (root == nullptr)
   { // initialize root and insert key
      root = make_shared<TreeNode>(TreeNode(true));
      root->keys.at(0) = key;
      root->values.at(0) = value;
      root->size = 1;
   }
   // tree root is full
   else if (root->size == 3)
   { // make new root node
      shared_ptr<TreeNode> newRoot = make_shared<TreeNode>(TreeNode(false));

      newRoot->children.at(0) = root;
      newRoot->split(0, root);

      int i = 0;
      if (newRoot->compare(newRoot->keys.at(0), key) == -1)
      {
         i++;
      }
      // root becomes newRoot with root keys as children
      newRoot->children.at(i)->insertSemi(key, value);
      root = newRoot;
   }
   // tree root is not full
   else
   { // keep inserting into the root
      root->insertSemi(key, value);
   }
}

// Find a key in the index, return -1 if not found
int Index::Find(shared_ptr<string> key) const
{
   shared_ptr<TreeNode> findPtr = search(key);

   if (findPtr != nullptr)
   { // if key found
      return findPtr->values.at(findPtr->findIndex(key));
   }
   // not found
   return -1;
}

// Remove a key from the index
void Index::Remove(shared_ptr<string> key)
{
   if (!root)
   { // tree is empty
      return;
   }

   root->remove(key);

   if (root->size == 0)
   { // root is empty
      shared_ptr<TreeNode> temp = root;

      if (root->isLeaf)
      {
         root = nullptr;
      }
      else
      { // first child becomes root
         root = root->children[0];
      }
   }
}

void Index::printPair(shared_ptr<string> key, int value)
{
   cout << *key << ", " << value << endl;
}

// print entire index inorder
void Index::InOrderVisit(function<void(shared_ptr<string>, int)> visit)
{
   if (root != nullptr)
   { // only print tree if not empty
      root->inOrderVisit(visit);
   }
}

void Index::parseBook()
{
   fstream file;
   string word, t, q;
   string filename = "book.txt";
   file.open(filename.c_str());

   auto isAlphaNum = [](char c)
   {
      return (c > 64 && c < 91) || (c > 96 && c < 123) || (c > 47 && c < 58);
   };

   while (file >> word)
   {
      int begin = 0;
      int end = word.size();

      for (unsigned int i = 0; i < word.size() && !isAlphaNum(word[i]); i++)
      { // cut beginning punctuation marks
         begin++;
      }

      for (int i = word.size() - 1; i >= begin && !isAlphaNum(word[i]); i--)
      { // cut ending punctuaction marks
         end = i;
      }

      for (int i = begin; i < end; i++)
      { // lowercase everything
         word[i] = tolower(word[i]);
      }

      for (int i = end; i >= begin; i--)
      {
         if (word[i] == ' ')
         { // remove unnecessary spaces
            end--;
         }
      }

      if (word[end - 2] == '\'')
      { // 's string end (remove)
         end -= 2;
      }

      word = word.substr(begin, end - begin);

      if (word[0] != ' ' && (word[end] > 96 || word[end] < 123) && word.size() != 0)
      {
         int count = Find(make_shared<string>(word));

         if (Find(make_shared<string>(word)) == -1)
         { // if adding for the first time, initialize the count
            Insert(make_shared<string>(word), 1);
         }
         else
         { // increment current count
            Insert(make_shared<string>(word), count + 1);
         }
      }
   }
}

// Helper function to find node where key is located
shared_ptr<TreeNode> Index::search(shared_ptr<string> key) const
{
   shared_ptr<TreeNode> curPtr = root;

   while (curPtr != nullptr)
   {
      int i = 0;
      while (i < curPtr->size && curPtr->compare(key, curPtr->keys.at(i)) == 1)
      { // increment index until key equal or greater than
         i++;
      }

      if (i < curPtr->size && curPtr->compare(curPtr->keys.at(i), key) == 0)
      { // key found, return node
         return curPtr;
      }
      else if (curPtr->isLeaf == true)
      { // key not found, end reached
         return nullptr;
      }
      // if not found, continue searching
      curPtr = curPtr->children.at(i);
   }

   return nullptr;
}

bool Index::replaceIfExists(shared_ptr<string> key, int value)
{
   // check if value is negative, not allowed
   if (value < 0)
   {
      cout << "ERROR: Value can't be negative!" << endl;
      throw 10;
   }
   // if key exists, replace its value
   shared_ptr<TreeNode> findPtr = search(key);
   if (findPtr != nullptr)
   {
      int index = findPtr->findIndex(key);
      findPtr->values.at(index) = value;
      return true;
   }

   return false;
}