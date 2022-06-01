/* Created by Egor Kolyshkin on 01/25/2022 */

#ifndef JLT_FINDER_H
#define JLT_FINDER_H

#include <memory>

class Node;

using namespace std;
using ptr = shared_ptr<Node>;

class JltFinder
{
public:
   // public constructor, receives the root of the binary search tree over which to search
   JltFinder(ptr root);

   // search for the node with the value closest to but less than n
   ptr Find(int n) const;

   // returns root of tree which to search
   ptr getRoot() const;

private:
   // Find iterative helper
   ptr iterativeFind(int n, ptr curPtr) const;

   // Find recursive helper
   ptr recursiveFind(int n, ptr curPtr) const;

   // FIELDS:
   ptr root; // root of tree which to search
};

#endif // JLT_FINDER_H