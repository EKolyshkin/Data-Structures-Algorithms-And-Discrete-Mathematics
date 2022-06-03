/* Created by Egor Kolyshkin on 02/23/2022 */

#include "HashTable.h"
#include "HashFunction.h"

#include <string>
#include <iostream>

// Default HashNode constructor
HashNode::HashNode() {}

// Parameterized HashNode constructor
HashNode::HashNode(shared_ptr<string> key, int value)
    : key(key), value(value), next(nullptr), prev(nullptr) {}

// destructor
HashNode::~HashNode() {}

// Public constructor, indicates how large to make the initial table.
HashTable::HashTable(int size) : hash(make_shared<HashFunction>(HashFunction(size))) {}

// destructor
HashTable::~HashTable()
{
   for (shared_ptr<HashNode> curPtr : list)
   {
      if (curPtr != nullptr)
      {
         curPtr->prev = nullptr;

         while (curPtr->next != nullptr)
         {
            curPtr = curPtr->next;
            curPtr->prev->next = nullptr;
            curPtr->prev = nullptr;
         }

         curPtr->next = nullptr;
      }
   }
}

// Insert a key in the table
void HashTable::Insert(shared_ptr<string> key, int value)
{
   int index = hash->Hash(key);
   auto curPtr = list[index];

   if (curPtr == nullptr)
   { // key doesn't exist, insert as normal
      list[index] = make_shared<HashNode>(HashNode(key, value));
   }
   else
   { // nodes exist in index
      if (*curPtr->key == *key)
      { // if key already exists, replace value and don't insert
         curPtr->value = value;
         return;
      }

      while (curPtr->next != nullptr)
      {
         curPtr = curPtr->next;

         if (*curPtr->key == *key)
         { // if key already exists, replace value and don't insert
            curPtr->value = value;
            return;
         }
      }
      // if nodes exist in index, add new at the end of chain
      curPtr->next = make_shared<HashNode>(HashNode(key, value));
      curPtr->next->prev = curPtr;
   }
}

// is a key present in the table
bool HashTable::Contains(shared_ptr<string> key) const
{
   if (Get(key) == -1)
   {
      return false;
   }

   return true;
}

// Find a key in the index
int HashTable::Get(shared_ptr<string> key) const
{
   auto foundPtr = getPtr(key, hash->Hash(key));

   if (foundPtr != nullptr)
   { // key found
      return foundPtr->value;
   }
   // key not found
   return -1;
}

// Remove a node referenced by string.
void HashTable::Remove(shared_ptr<string> key)
{
   int index = hash->Hash(key);
   auto foundPtr = getPtr(key, index);

   if (foundPtr == nullptr)
   { // not found item
      return;
   }
   if (foundPtr == list[index])
   { // if found item is the first in the chain
      list[index] = foundPtr->next;
   }
   if (foundPtr->prev != nullptr)
   { // unlink left node
      foundPtr->prev->next = foundPtr->next;
   }
   if (foundPtr->next != nullptr)
   { // unlink right node
      foundPtr->next->prev = foundPtr->prev;
   }
}

// helper function to find pointer to any key
shared_ptr<HashNode> HashTable::getPtr(shared_ptr<string> key, int hash) const
{
   auto curPtr = list[hash];

   while (curPtr != nullptr)
   { // go through entire chain at index hash
      if (*curPtr->key == *key)
      { // key found
         return curPtr;
      }
      // keep searching otherwise
      curPtr = curPtr->next;
   }

   return nullptr;
}

// print table function for debugging
void HashTable::print() const
{
   for (int i = 0; i < defSize; i++)
   {
      auto ptr = list[i];

      if (ptr != nullptr)
      {
         cout << "[" << i << "]" << endl
              << endl;
      }

      while (ptr != nullptr)
      {
         cout << *ptr->key << " : " << ptr->value << endl;
         ptr = ptr->next;

         if (ptr == nullptr)
         {
            cout << endl;
         }
      }

      cout << endl;
   }
}