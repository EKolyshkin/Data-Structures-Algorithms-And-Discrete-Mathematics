/* Created by Egor Kolyshkin on 02/23/2022 */

#include "HashFunction.h"

#include <random>
#include <iostream>

// default constructor
HashFunction::HashFunction() : HashFunction(10000) {}

// Public Constructor
HashFunction::HashFunction(int size) : size(size)
{
   srand(time(0));

   for (int i = 0; i < maxBits; i++)
   { // fill randoms array with random stuff
      randoms[i] = rand();
   }
}

// destructor
HashFunction::~HashFunction() {}

// Compute hash for an arbitrarily long string
int HashFunction::Hash(shared_ptr<string> key) const
{
   vector<int> index;
   bitset<16> result;

   for (unsigned int i = 0; i < key->length(); i++)
   { // pick indexes of randoms array which to XOR
      bitset<8> ltr(key->at(i));

      for (int j = 0; j < 8; j++)
      { // go through each bit
         if (ltr[j] == 1)
         { // if bit is 1, add its index for randoms array
            // modulus maxBits to not go over array size
            index.push_back((i * 8 + j) % maxBits);
         }
      }
   }

   for (int i : index)
   { // XOR result with bitset from randoms array
      result ^= randoms[i];
   }

   return result.to_ulong() % size;
}

// print function for debugging
void HashFunction::print() const
{
   cout << "Random Numbers Table" << endl
        << endl;

   for (int i = 0; i < maxBits; i++)
   {
      cout << randoms[i] << endl;
   }

   cout << endl;
}