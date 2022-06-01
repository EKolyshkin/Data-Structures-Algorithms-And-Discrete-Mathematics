/* Created by Egor Kolyshkin on 02/23/2022 */

#ifndef INDEX_H
#define INDEX_H

#include <memory>

using namespace std;

class HashTable;

class Index
{
public:
   // public constructor
   Index();

   // destructor
   ~Index();

   // Insert an element in the index, associate the integer value with the element
   void Insert(shared_ptr<string> element, int value);

   // Find an element in the index
   int Find(shared_ptr<string> element) const;

   // Remove an element from the index
   void Remove(shared_ptr<string> element);

   // print table function for debugging
   void print() const;

private:
   // table of hashes that stores all elements and their associated values
   shared_ptr<HashTable> table;
};

#endif // INDEX_H