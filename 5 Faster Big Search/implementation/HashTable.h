/* Created by Egor Kolyshkin on 02/23/2022 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <memory>

using namespace std;

const int defSize = 10000; // size of hash table

class HashFunction;

struct HashNode
{
   friend class HashTable;

public:
   // default constructor
   HashNode();

   // HashNode holds keys, values, and next pointer
   HashNode(shared_ptr<string> key, int value);

   // destructor
   ~HashNode();

private:
   // dictionary key
   shared_ptr<string> key;

   // dictionary value
   int value;

   // pointer to next node
   shared_ptr<HashNode> next;

   // pointer to previous node
   shared_ptr<HashNode> prev;
};

class HashTable
{
public:
   // Public constructor, indicates how large to make the initial table.
   HashTable(int size);

   // destructor
   ~HashTable();

   // Insert a key in the table
   void Insert(shared_ptr<string> key, int value);

   // is a key present in the table
   bool Contains(shared_ptr<string> key) const;

   // Find a key in the index
   int Get(shared_ptr<string> key) const;

   // Remove a node referenced by string.
   void Remove(shared_ptr<string> key);

   // print table function for debugging
   void print() const;

private:
   // function that hashes all entries in the table
   shared_ptr<HashFunction> hash;

   // list of paired elements and values
   shared_ptr<HashNode> list[defSize];

   // helper function to find pointer to any key
   shared_ptr<HashNode> getPtr(shared_ptr<string> key, int hash) const;
};

#endif // HASHTABLE_H