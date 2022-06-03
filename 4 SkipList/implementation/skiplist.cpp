
// modified by mashhadi on 14th feb to add an alternative op<<
// Modified by Egor Kolyshkin on 11/12/21.

#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

// SNODE

// constructor that sets node value
SNode::SNode(int value) : value{value} {}

// SKIPLIST

// constructor that sets max level of list and probability of inserting at
// higher level
SkipList::SkipList(int maxLevel, int probability)
    : maxLevel{maxLevel}, probability{probability} {
   // checks preconditions
   assert(maxLevel>0&&probability >= 0 && probability < 100);
   makeLevels();
}

// destructor
SkipList::~SkipList()
{
   deleteLevels();
   delete[] FrontGuards;
   delete[] RearGuards;
}

// deletes all levels of skiplist
void SkipList::deleteLevels()
{
   // for each level starting from the top
   for (int i = maxLevel - 1; i >= 0; i--)
   {
      SNode *curPtr = FrontGuards[i];

      while (curPtr != nullptr)
      {
         SNode *delPtr = curPtr;
         curPtr = curPtr->forward;

         delPtr->up = nullptr;
         delPtr->down = nullptr;
         delPtr->backward = nullptr;
         delPtr->forward = nullptr;
         delete delPtr;
         delPtr = nullptr;
      }
   }
}

// MUTATORS

// prints all levels of skiplist including guard node values
ostream &operator<<(ostream &Out, const SkipList &SkipL)
{
   for (int Index = SkipL.maxLevel - 1; Index >= 0; Index--)
   {
      Out << "Level: " + to_string(Index) + " -- ";
      SNode *Curr = SkipL.FrontGuards[Index];

      while (Curr != nullptr)
      {
         Out << to_string(Curr->value) + ", ";
         Curr = Curr->forward;
      }

      Out << "\n";
   }

   return Out;
}

// creates all levels of skiplist
void SkipList::makeLevels()
{
   // create first level guard nodes and link them together
   FrontGuards = new SNode *[maxLevel];
   RearGuards = new SNode *[maxLevel];
   FrontGuards[0] = new SNode(INT_MIN);
   RearGuards[0] = new SNode(INT_MAX);
   connectTwoHorizontally(FrontGuards[0], RearGuards[0]);

   // create higher levels
   for (int level = 1; level < maxLevel; level++)
   {
      // create guard nodes and link them together
      FrontGuards[level] = new SNode(INT_MIN);
      RearGuards[level] = new SNode(INT_MAX);
      connectTwoHorizontally(FrontGuards[level], RearGuards[level]);

      // link previous level to current level
      connectTwoVertically(FrontGuards[level - 1], FrontGuards[level]);
      connectTwoVertically(RearGuards[level - 1], RearGuards[level]);
   }
}

// adds an int value to list
// returns true if successful
// false otherwise
bool SkipList::add(int value)
{
   int level = 0;
   SNode *prevNode; // previously inserted node to connect up and down to

   do
   {
      SNode *newNode = new SNode(value);
      SNode *curPtr = FrontGuards[level];

      // find first value larger or equal to insert
      while (value > curPtr->forward->value)
      {
         curPtr = curPtr->forward;
      }
      // if contains value
      if (curPtr->forward->value == value)
      { // dont add
         delete newNode;
         return false;
      }
      else
      { // add value before next larger value
         addBefore(newNode, curPtr->forward);
      }

      // connect previous node to current up and down
      if (level > 0)
      {
         connectTwoVertically(prevNode, newNode);
      }

      level++;
      prevNode = newNode;
   } while (level < maxLevel && shouldInsertAtHigher());

   return true;
}

// adds a vector of values to list
// returns true if ALL items from vector were added
// false otherwise
bool SkipList::add(const vector<int> &values)
{
   bool noDups = true;

   // parses each vector value and adds it individually
   for (int i = 0; i < values.size(); i++)
   {
      if (!add(values[i]))
      { // found a duplicate
         noDups = false;
      }
   }

   return noDups;
}

// removes an int value from list
// returns true if successful
// false otherwise
bool SkipList::remove(int value)
{
   SNode *curNode = containsSNode(value); // will always be topmost node

   if (curNode == nullptr)
   {
      return false; // nothing to remove
   }

   while (curNode != nullptr)
   {
      // connect horizontally left and right nodes
      connectTwoHorizontally(curNode->backward, curNode->forward);

      // remove horizontal pointers
      curNode->backward = nullptr;
      curNode->forward = nullptr;

      // previous node to delete
      SNode *delNode = curNode;

      // move to next level
      curNode = curNode->down;

      // delete previous node
      delNode->up = nullptr;
      delNode->down = nullptr;
      delete delNode;
      delNode = nullptr;
   }

   return true;
}

// Given a SNode, place it before the given NextNode
void SkipList::addBefore(SNode *NewNode, SNode *NextNode)
{
   // Link next to node in front
   NewNode->forward = NextNode;
   // Link prev to node behind
   NewNode->backward = NextNode->backward;
   // Link node in back to new node
   NextNode->backward->forward = NewNode;
   // Link node in front to new node
   NextNode->backward = NewNode;
}

// private method to connect 2 nodes forward and backward
void SkipList::connectTwoHorizontally(SNode *left, SNode *right)
{
   left->forward = right;
   right->backward = left;
}

// private method to connect 2 nodes up and down
void SkipList::connectTwoVertically(SNode *lower, SNode *higher)
{
   lower->up = higher;
   higher->down = lower;
}

// checks if node should be inserted at higher level
// returns true if it should be inserted
// false otherwise
bool SkipList::shouldInsertAtHigher() const
{
   return (rand() % 100) < probability;
}

// Checks to see whether or not a data value exists in the list
// Returns the NODE if the value exists in the SkipList.
// Returns nullptr otherwise
SNode *SkipList::containsSNode(int value) const
{
   SNode *foundNode = nullptr;
   int level = maxLevel - 1;

   // search for value starting from top layer
   SNode *curPtr = FrontGuards[level];

   while (foundNode == nullptr)
   {
      // find first value larger than insert
      while (curPtr->forward->value < value)
      {
         curPtr = curPtr->forward;
      }
      // if value is found
      if (curPtr->forward->value == value)
      {
         foundNode = curPtr->forward;
      }
      // go down a level and keep searching
      else
      { // if not at the bottom yet
         if (curPtr->down != nullptr)
         { // move down
            curPtr = curPtr->down;
         }
         else
         {
            return nullptr;
         }
      }
   }

   return foundNode;
}

// Checks to see whether or not a data value exists in the list
// Returns true if the value exists in the SkipList.
// Returns false otherwise
bool SkipList::contains(int value) const
{
   return (containsSNode(value) != nullptr);
}
