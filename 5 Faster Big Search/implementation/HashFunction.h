/* Created by Egor Kolyshkin on 02/23/2022 */

#ifndef HASHFUNCTION_H
#define HASHFUNCTION_H

#include <memory>
#include <bitset>

using namespace std;

static const int maxBits = 512;

class HashFunction
{
public:
   // default constructor
   HashFunction();

   // Public Constructor
   HashFunction(int size);

   // destructor
   ~HashFunction();

   // Compute hash for an arbitrarily long string
   int Hash(shared_ptr<string> key) const;

   // print function for debugging
   void print() const;

private:
   // size of the hash table
   int size;

   // array of random numbers
   bitset<16> randoms[maxBits];

};

#endif // HASHFUNCTION_H