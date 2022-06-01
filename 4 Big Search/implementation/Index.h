/* Created by Egor Kolyshkin on 02/08/2022 */

#ifndef INDEX_H
#define INDEX_H

#include <memory>
#include <vector>
#include <functional>

using namespace std;

class TreeNode;

class Index
{
public:
   // default constructor
   Index();

   // destructor
   ~Index();

   /* Insert a key in the index, associate the integer value with the key
   replace value of key if key already exists */
   void Insert(shared_ptr<string> key, int value);

   // Find a key in the index, return -1 if not found
   int Find(shared_ptr<string> key) const;

   // Remove a key from the index
   void Remove(shared_ptr<string> key);

   // parse book to add all words to tree and number of occurrences
   void parseBook();

   // print key and its value
   void printPair(shared_ptr<string>, int);

   // traverse entire index inorder
   void InOrderVisit(function<void(shared_ptr<string>, int)> visit);


private:
   // FIELDS:
   shared_ptr<TreeNode> root; // root of 2-3 tree

   // Helper function to find node where key is located
   shared_ptr<TreeNode> search(shared_ptr<string> key) const;

   // Helper function to replace existing key's value
   bool replaceIfExists(shared_ptr<string> key, int value);
};

#endif // INDEX_H