/* Created by Egor Kolyshkin on 01/15/2022 */

#include "Encoder.h"
#include "HuffNode.h"

#include <bitset>
#include <iostream>

const char delimiter = '{'; 

// constructor passing array of letter frequencies
Encoder::Encoder(shared_ptr<vector<int>> frequencyVector) : root(nullptr)
{
   // throw error if input invalid
   checkFrequencyInput(frequencyVector);

   // create vector of leaf nodes for each character frequency
   // frequencyVector[0] = 'a', frequencyVector[25] = 'z' 
   vector<shared_ptr<HuffNode>> leafNodes = {};

   // define 27th character with freq 0 that represents a stop in message
   frequencyVector->push_back(0); // frequencyVector[26] = delimiter

   // create a new leaf node for each character
   for (unsigned int i = 0; i < frequencyVector->size(); i++)
   {
      // insert new leaf node in order
      int index = findInsertIndex(leafNodes, frequencyVector->at(i));
      leafNodes.insert(leafNodes.begin() + index, make_shared<HuffNode>
            (HuffNode(frequencyVector->at(i), 97 + i, nullptr, nullptr)));
   }

   // combine nodes until there is one root node left
   while (leafNodes.size() > 1)
   {
      // make tree with values and root = sum frequency
      // "X" (capital) represents junction node
      shared_ptr<HuffNode> min1 = leafNodes.at(leafNodes.size() - 1);
      shared_ptr<HuffNode> min2 = leafNodes.at(leafNodes.size() - 2);
      int sum = min1->frequency + min2->frequency;
      shared_ptr<HuffNode> sumPtr = make_shared<HuffNode>
                                       (HuffNode(sum, 88, min2, min1));

      // erase two smallest elements
      leafNodes.erase(leafNodes.end() - 1);
      leafNodes.erase(leafNodes.end() - 1);

      // insert sum tree in order
      int index = findInsertIndex(leafNodes, sumPtr->frequency);
      leafNodes.insert(leafNodes.begin() + index, sumPtr);
   }

   this->root = leafNodes.at(0);
}

// finds where to insert value in vector in proper order
int Encoder::findInsertIndex(vector<shared_ptr<HuffNode>> leafNodes, int value) const
{
   unsigned int index = 0;

   while (index < leafNodes.size() && value < leafNodes.at(index)->frequency)
   {
      index++;
   }

   return index;
}

// encode string into a sequence of bytes
shared_ptr<vector<char>> Encoder::Encode(string messageString)
{
   // throw error if input invalid
   checkMessageInput(messageString);

   messageString.push_back(delimiter); // add delimiter to end of message
   this->encodedMessage = {}; // reset previous encoded message
   string fullMessage = "";   // message in bits
   
   // encode each character by adding its huffman value
   // to the vector sequence in chunks of chars
   for (char character : messageString)
   {  // find code for each character
      string code = "";
      encodeChar(character, getRoot(), code);
      fullMessage.append(code);
   }

   // add bits from string to encoded message
   for (unsigned int i = 0; i < fullMessage.size(); i += 8)
   {
      char character = packChar(fullMessage.substr(i, 8));
      this->encodedMessage.push_back(character);
   }

   return getEncoded();
}

// finds binary huffman number for letter
bool Encoder::encodeChar(char letter, shared_ptr<HuffNode> root, string& path) const
{
   if (root == nullptr)
   {  // character not found
      return false;
   }

   if (root->character == letter)
   {  // character found
      return true;
   }

   if (encodeChar(letter, root->left, path))
   {  // go left
      path.insert(path.begin(), '0');
      return true;
   }
   
   if (encodeChar(letter, root->right, path))
   {  // go right
      path.insert(path.begin(), '1');
      return true;
   }
   // catch-all
   return false;
}

// pack 8 bits of string into 1 char
char Encoder::packChar(string byteMessage) const
{
   char c = 0;
   int size = byteMessage.size();

   // for all 8 bits or less, pack char c with those bits
   for (int i = 0; i < 8 && i < size; i++)
   {
      c |= (byteMessage[i] == '1') << (7 - i);
   }

   return c;
}

// decode an array of bytes into a string
string Encoder::Decode(shared_ptr<vector<char>> encodedVector)
{
   string message = ""; // decoded message
   auto rootPtr = getRoot();

   // go through all bytes in vector
   for (char byte : *encodedVector)
   {
      string bits = bitset<8> (byte).to_string(); // bits in each byte
      
      for (char direction : bits)
      {
         if (direction == '0')
         {  // go left
            rootPtr = rootPtr->left;
         }
         else if (direction == '1')
         {  // go right
            rootPtr = rootPtr->right;
         }

         char character = rootPtr->character;

         if (character == delimiter)
         {  // stop message
            return message;
         }
         else if (character != 'X')
         {  // add letter
            message += character;
            rootPtr = getRoot();
         }
      }
   }

   return message;
}

// print a huffnode vector backwards
void Encoder::printBackwards(vector<shared_ptr<HuffNode>> vector) const
{
   // iterate through vector (smallest on top)
   for (int i = vector.size() - 1; i >= 0; i--)
   {
      cout << vector.at(i)->character << ":" << vector.at(i)->frequency << ", ";
   }
   cout << endl;
}

// prints Huffman tree horizontally left to right
void Encoder::printTree() const
{
   printTree(getRoot(), 0);
}

// (helper) prints Huffman tree horizontally left to right
void Encoder::printTree(shared_ptr<HuffNode> root, int space) const
{
   // space between tree levels
   space += 20;
   
   if (root == nullptr)
   {  // base case
      return;
   }

   // print right side first (at the top)
   printTree(root->right, space);
   cout << endl;

   for (int i = 0; i < space; i++)
   {  // prepend spaces for each level
      cout << " ";
   }

   // print character, then left side (at the bottom)
   cout << root->character << ":" << root->frequency << endl;
   printTree(root->left, space);
}

// throws error if frequency vector does not contain all frequencies
void Encoder::checkFrequencyInput(shared_ptr<vector<int>> frequencyVector) const
{
   int size = frequencyVector->size();

   if (size != 26)
   {
      throw ("ERROR: Frequency vector not 26 characters! Size: " + to_string(size));
   }

   for (int i : *frequencyVector)
   {
      if (i < 1)
      {
         throw "ERROR: Frequency vector contains invalid frequency: '" + i;
      }
   }
}

// throws error if message contains odd characters
void Encoder::checkMessageInput(string messageString) const
{
   if (messageString.empty())
   {
      throw "ERROR: Message string is empty!";
   }
   
   for (char character : messageString)
   {
      if (character > 'z' || character < 'a' || character == ' ')
      {
         cout << "ERROR: Message string contains invalid character: " << "'" << character << "'" << endl;
         throw "ERROR"; 
      }
   }
}

// returns root of tree
shared_ptr<HuffNode> Encoder::getRoot() const
{
   return this->root;
}

// returns pointer to encoded message
shared_ptr<vector<char>> Encoder::getEncoded() const
{
   return make_shared<vector<char>> (this->encodedMessage);
}