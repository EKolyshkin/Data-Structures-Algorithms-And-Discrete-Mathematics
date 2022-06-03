/**
 * SkipList https://en.wikipedia.org/wiki/Skip_list
 * also used by MemSQL
 * https://www.singlestore.com/blog/what-is-skiplist-why-skiplist-index-for-memsql/
 * SkipList with a depth of 1 is similar to a doubly-linked list
 * Each item has a p percent chance of being at the next level up
 * For our implementation p = 50%
 * All elements are inserted at the lowest Depth (1)
 * 50% of the elements inserted in Depth = 2
 * 50% of 50%, or 25% of the elements inserted in Depth = 3
 * and so on
 *
 * If a Skip List has only 1 level, such as p = 0%
 * Insert O(n), Search O(n)
 * For Depth > 1
 * Insert O(log n), Search O(log n)
 * Modifying p allows us to trade off search speed and storage cost
 *
 */

#ifndef ASS4_SKIPLIST_H
#define ASS4_SKIPLIST_H

#include <iostream>
#include <vector>

using namespace std;

// only SkipList class can create SNode objects

class SkipList;

class SNode
{
   friend class SkipList;
   friend ostream &operator<<(ostream &out,
                              const SkipList &skip); // print operator

 private:
   explicit SNode(int value); // constructor
   int value;                 // data contained in the object
   SNode *forward;            // link to Next SNode
   SNode *backward;           // link to Prev SNode
   SNode *up;                 // link to up node
   SNode *down;               // link to down SNode
};

class SkipList
{
   friend ostream &operator<<(ostream &out,
                              const SkipList &skip); // display with level

 public:
   // constructor
   // default SkipList has only 1 level, just one doubly-linked list
   explicit SkipList(int maxLevel = 1, int probability = 0);

   // destructor
   virtual ~SkipList();

   SkipList(const SkipList &other) = delete; // copy not allowed
   SkipList(SkipList &&other) = delete;      // move not allowed
   SkipList &
   operator=(const SkipList &other) = delete; // assignment not allowed
   SkipList &
   operator=(SkipList &&other) = delete; // move assignment not allowed

   // return true if successfully added, no duplicates allowed
   bool add(int value);

   // returns true if ALL items from vector were added
   bool add(const vector<int> &values);

   // return true if data successfully removed
   bool remove(int value);

   // return true if data found in SkipList
   bool contains(int value) const;

 private:
   int maxLevel;        // total number of levels
   int probability;     // probability of inserting at a higher level
                        // as an integer between 0% and 100% (exclusive)
   SNode **FrontGuards; // array of maxLevel SNode* objects as FrontGuards
                        // linking levels
   SNode **RearGuards; // array of maxLevel SNode* objects as RearGuards linking
                       // levels

   // creates all levels of skiplist
   void makeLevels();

   // deletes all levels of skiplist
   void deleteLevels();

   // given a SNode, place it before the given nextNode
   void addBefore(SNode *newNode, SNode *nextNode);

   // return true p% of time,
   // for p = 50, each node has a 50% chance of being at higher level
   bool shouldInsertAtHigher() const;

   // connect 2 nodes forward and backward
   static void connectTwoHorizontally(SNode *left, SNode *right);

   // connect 2 nodes up and down
   static void connectTwoVertically(SNode *lower, SNode *higher);

   // checks to see whether or not a data value exists in the list
   SNode *containsSNode(int value) const;
};

#endif // ASS4_SKIPLIST_H
