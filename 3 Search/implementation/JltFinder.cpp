/* Created by Egor Kolyshkin on 01/25/2022 */

#include "JltFinder.h"
#include "Node.h"

// public constructor, receives the root of the binary search tree over which to search
JltFinder::JltFinder(ptr root) : root{root}
{
}

// search for the node with the value closest to but less than n
ptr JltFinder::Find(int n) const
{
   return iterativeFind(n, getRoot());
   // return recursiveFind(n, getRoot());
}

// Find iterative helper
ptr JltFinder::iterativeFind(int n, ptr curPtr) const
{
   ptr jltPtr = nullptr; // JLT value pointer

   while (curPtr != nullptr)
   {  // search until we go too far right
      if (curPtr->getValue() < n)
      {  // if value is less than, search right side
         jltPtr = curPtr;
         curPtr = curPtr->getRight();
      }
      else
      {  // if value is more than, search left side
         curPtr = curPtr->getLeft();
      }
   }

   return jltPtr;
}

// Find recursive helper
ptr JltFinder::recursiveFind(int n, ptr curPtr) const
{
   if (curPtr == nullptr)
   {  // if no value less than n, return nullptr
      return nullptr;
   }

   int curValue = curPtr->getValue();

   if (curValue < n)
   {  // if value is less than, search right side
      ptr rightPtr = recursiveFind(n, curPtr->getRight());

      if (rightPtr == nullptr)
      {  // if bigger value not found, return current value
         return curPtr;
      }

      // if bigger value found, return bigger value
      return rightPtr;
   }

   if (curValue > n)
   {  // if value is more than, search left side
      return recursiveFind(n, curPtr->getLeft());
   }

   // catch-all return statement
   return nullptr;
}

// returns root of tree which to search
ptr JltFinder::getRoot() const
{
   return this->root;
}
