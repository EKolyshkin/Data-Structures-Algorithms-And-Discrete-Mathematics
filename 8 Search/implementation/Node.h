/* Created by Egor Kolyshkin on 01/25/2022 */

#ifndef NODE_H
#define NODE_H

#include <memory>

using namespace std;

class Node
{
public:
   // constructor
   Node(int value, shared_ptr<Node> left = nullptr, shared_ptr<Node> right = nullptr)
                                    : value{value}, left{left}, right{right} {}

   // destructor
   // ~Node();

   // get value of the node
   int getValue() const { return this->value; };

   // get pointer to left node
   shared_ptr<Node> getLeft() const { return this->left; }; 
   
   // get pointer to right node
   shared_ptr<Node> getRight() const { return this->right; };

   shared_ptr<Node> insert(shared_ptr<Node> root, int value)
   {
      if (!root)
      {
         return make_shared<Node> (Node(value));
      }

      if (value > root->getValue())
      {
         root->right = insert(root->getRight(), value);
      }
      else
      {
         root->left = insert(root->getLeft(), value);
      }
      
      return root;
   }

private:

   // FIELDS:
   int value;  // value of node
   shared_ptr<Node> left;  // pointer to left
   shared_ptr<Node> right; // pointer to right
};



#endif // NODE_H