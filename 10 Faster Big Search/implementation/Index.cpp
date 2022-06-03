/* Created by Egor Kolyshkin on 02/23/2022 */

#include "Index.h"
#include "HashTable.h"

// public constructor
Index::Index() : table(make_shared<HashTable>(HashTable(defSize))) {}

// destructor
Index::~Index() {}

// Insert a key in the index, associate the integer value with the key
void Index::Insert(shared_ptr<string> key, int value)
{
   if (value < 0)
   {
      throw 10;
   }

   table->Insert(key, value);
}

// Find a key in the index
int Index::Find(shared_ptr<string> key) const
{
   return table->Get(key);
}

// Remove a key from the index
void Index::Remove(shared_ptr<string> key)
{
   table->Remove(key);
}

// print table function for debugging
void Index::print() const
{
   table->print();
}