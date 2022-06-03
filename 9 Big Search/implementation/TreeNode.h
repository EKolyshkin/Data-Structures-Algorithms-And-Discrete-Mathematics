/* Created by Egor Kolyshkin on 02/08/2022 */

#ifndef TREENODE_H
#define TREENODE_H

#include <memory>
#include <string>
#include <vector>
#include <functional>

using namespace std;

class TreeNode
{
   friend class Index;

public:
   // parameterized constructor
   TreeNode(bool isLeaf);

   // destructor
   ~TreeNode();

   // compare two string pointers -1 if left less, 1 if right less, 0 if equal
   int compare(shared_ptr<string> left, shared_ptr<string> right) const;

private:
   // FIELDS:
   vector<shared_ptr<string>> keys;       // vector of all keys
   vector<int> values;                    // vector of all values
   vector<shared_ptr<TreeNode>> children; // vector of all child pointers
   int size;                              // current number of keys
   bool isLeaf;                           // true if node is leaf

   // Helper Insert a key in subtree of semi-full node
   void insertSemi(shared_ptr<string> key, int value);

   // Helper Insert split full child childPtr with index index in vector children
   void split(int index, shared_ptr<TreeNode> childPtr);

   // Helper function to print node inorder recursively
   void inOrderVisit(function<void(shared_ptr<string>, int)> visit) const;

   // Helper search finds index to which key and value are associated
   int findIndex(shared_ptr<string> key) const;

   // Helper remove function for index key
   void remove(shared_ptr<string> key);

   // Helper remove key at index from leaf node
   void removeLeaf(int index);

   // Helper remove key at index from middle node
   void removeMiddle(int index);

   // get previous index to key parent
   shared_ptr<string> getPrev(int index, int &value);

   // get next index to key parent
   shared_ptr<string> getNext(int index, int &value);

   // fill child node at index
   void fill(int index);

   // move previous child to current index
   void borrowPrev(int index);

   // move next child to current index
   void borrowNext(int index);

   // merge two children at index and index + 1
   void merge(int index);
};

#endif // TREENODE_H