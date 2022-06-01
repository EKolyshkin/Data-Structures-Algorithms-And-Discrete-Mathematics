/* Created by Egor Kolyshkin on 01/25/2022 */

#include "JltFinder.h"
#include "Node.h"
#include "Student.h"

#include <iostream>

using namespace std;
using ptr = shared_ptr<Node>;

void testStudent()
{
   cout << endl;
   Student me = Student();
   cout << "Created by: ";
   cout << me.FirstName() << " ";
   cout << me.LastName() << endl;
   cout << "Student ID: ";
   cout << me.StudentIdentifier();
   cout << endl << endl;
}

void emptyTreeTest()
{
   JltFinder test(nullptr);

   if (test.Find(5) == nullptr)
   {
      cout << "Empty tree test passed!" << endl;
   }
   else 
   {
      cout << "Empty tree test failed!" << endl;
   }
}

void singleNodeTest()
{
   Node testNode(20, nullptr, nullptr);
   JltFinder test(make_shared<Node> (testNode));
   int foundValue = test.Find(21)->getValue();

   if (foundValue < 21)
   {
      cout << "Single node test passed! Value: " << foundValue << endl;
   }
   else
   {
      cout << "Single node test failed!" << endl;
   }
}

void twoLeftNodeTest()
{
   Node testNode(20, make_shared<Node> (Node(5)));
   JltFinder test(make_shared<Node> (testNode));
   int n = 6;
   int foundValue = test.Find(n)->getValue();

   if (foundValue < n)
   {
      cout << "Two left node test passed! Value: " << foundValue << endl;
   }
   else
   {
      cout << "Two left node test failed!" << endl;
   }
}

void threeNodeTest()
{
   Node testNode(8, make_shared<Node> (Node(5)), make_shared<Node> (Node(73)));
   JltFinder test(make_shared<Node> (testNode));
   int n = 75;
   int foundValue = test.Find(n)->getValue();

   if (foundValue < n)
   {
      cout << "Three node test passed! Value: " << foundValue << endl;
   }
   else
   {
      cout << "Three node node test failed!" << endl;
   }
}

void fullTreeTest()
{
   Node testNode(0,
   make_shared<Node> (Node(-2, make_shared<Node> (Node(-3)), make_shared<Node> (Node(-1)))),
   make_shared<Node> (Node(5, make_shared<Node> (Node(2)), make_shared<Node> (Node(25)))));
   JltFinder test(make_shared<Node> (testNode));

   int n = 0;
   int foundValue = test.Find(n)->getValue();

   if (foundValue < n)
   {
      cout << "Full tree test passed! Value: " << foundValue << endl;
   }
   else
   {
      cout << "Full tree test failed!" << endl;
   }

   if (test.Find(-13) == nullptr)
   {
      cout << "Full tree invalid value passed!" << endl;
   }
   else
   {
      cout << "Full tree invalid value failed!" << endl;
   }
}

int main()
{
   testStudent();
   emptyTreeTest();
   singleNodeTest();
   twoLeftNodeTest();
   threeNodeTest();
   fullTreeTest();

   return 0;
}