/* Created by Egor Kolyshkin on 01/15/2022 */

#ifndef HUFFNODE_H
#define HUFFNODE_H

#include <memory> // for shared_ptr

using namespace std;

class HuffNode
{
public:
   int frequency; // character frequency
   char character; // ascii value of character (97-123, 'a'-'z' + '{')
   shared_ptr<HuffNode> left; // left pointer, bigger side (0)
   shared_ptr<HuffNode> right; // right pointer, smaller side (1)

   // constructor with default as leaf node
   explicit HuffNode(int frequency, char character, shared_ptr<HuffNode> left = nullptr,
      shared_ptr<HuffNode> right = nullptr) : frequency{frequency}, character{character},
      left{left}, right{right}
   {
   }
};

#endif // HUFFNODE_H