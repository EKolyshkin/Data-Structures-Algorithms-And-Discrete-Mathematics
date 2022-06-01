/* Created by Egor Kolyshkin on 01/15/2022 */

#ifndef ENCODER_H
#define ENCODER_H

#include <string>
#include <vector>
#include <memory>

using namespace std;

class HuffNode; 

class Encoder
{
public:
   // constructor passing array of letter frequencies
   Encoder(shared_ptr<vector<int>> frequencyVector);

   // encode string into a sequence of bytes
   shared_ptr<vector<char>> Encode(string messageString); 

   // decode an array of bytes into a string
   string Decode(shared_ptr<vector<char>> encodedVector);

   // prints Huffman tree horizontally left to right
   void printTree() const;

   // returns root of tree
   shared_ptr<HuffNode> getRoot() const;

   // returns pointer to encoded message
   shared_ptr<vector<char>> getEncoded() const;

private:
   // finds where to insert value in vector in proper order
   int findInsertIndex(vector<shared_ptr<HuffNode>> leafNodes, int value) const;
   
   // finds binary huffman number for letter
   bool encodeChar(char letter, shared_ptr<HuffNode> root, string &path) const;

   // pack 8 bits of string into 1 char
   char packChar(string byteMessage) const;

   // print a huffnode vector backwards
   void printBackwards(vector<shared_ptr<HuffNode>> vector) const;

   // (helper) prints Huffman tree horizontally left to right
   void printTree(shared_ptr<HuffNode> root, int space) const;

   // throws error if frequency vector does not contain all frequencies
   void checkFrequencyInput(shared_ptr<vector<int>> frequencyVector) const;

   // throws error if message contains odd characters
   void checkMessageInput(string messageString) const;

   // FIELDS:
   shared_ptr<HuffNode> root; // root of huffman tree 
   vector<char> encodedMessage; // encoded message
};

#endif // ENCODER_H
