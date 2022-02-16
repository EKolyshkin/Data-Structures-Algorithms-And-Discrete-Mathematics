 /*
 * Modified by Kye Nelson & Egor Kolyshkin on 12/11/2021.
 * Main test class
 * 
 * Test 0 - tests general methods: empty trr, add, accessors, copy constructors
 * Test 1 - tests remove function.
 * Test 2 - tests copy contructor. asserts to check its not a shallow copy.
 * Test 3 - test sort function to sort array into pre order form.
 * Final Test - Final required test that asks for user input of a single integer.
 * outputs tree of integers 1..n. Copies tree and outputs copied tree along with
 * the copied tree with all even values removed.
 */

#include <iostream>
#include <cassert>

#include "ThreadedBST.h"

using namespace std;

void test0()
{
  ThreadedBST emptyTree{}; // empty tree, use brackets {} to call default constructor
  assert(emptyTree.getDepth() == -1);
  assert(emptyTree.isEmpty());
  cout << emptyTree << endl;
  
  ThreadedBST t1(3); // no branches tree

  cout << t1 << endl; // test inorder traversal
  assert(t1.getDepth() == 0);
  assert(!t1.isEmpty());

  t1.add(5); // add stuff
  t1.add(2);
  cout << t1 << endl;
  assert(t1.getDepth() == 1);
  assert(t1.getNumberOfNodes() == 3);
  // assert(t1.contains(5));

  t1.add(1); // add stuff
  cout << t1 << endl;
  assert(t1.getDepth() == 2);
  assert(t1.contains(1));
  assert(!t1.add(1));

  // test copy constructor
  ThreadedBST t2(t1);
  cout << t2 << endl;

  // t1.add(4);
  // cout << t1 << endl;
  // assert(t1.getHeight() == 2);
}

void test1() //test remove
{
  ThreadedBST t1;
  t1.add(6);
  t1.add(3);
  t1.add(2);
  t1.add(4);
  t1.add(5);
  t1.add(1);
  t1.add(9);
  t1.add(8);
  t1.add(10);
  t1.add(7);
  t1.add(11);
  t1.add(12);
  cout << "t1 pre: " << t1 << endl;
  t1.remove(1);
  t1.remove(2);
  assert(t1.contains(2) == false);
  t1.remove(3);
  t1.remove(4);
  t1.remove(5);
  t1.remove(6);
  t1.remove(7);
  t1.remove(8);
  t1.remove(9);
  t1.remove(10);
  t1.remove(11);
  t1.remove(12);
  assert(t1.getNumberOfNodes() == 0);
  cout << "t1 post: " << t1 << endl;
}

void test2() // test copy constructor
{
  ThreadedBST t1;
  t1.add(4);
  t1.add(2);
  t1.add(6);
  t1.add(3);
  t1.add(1);
  t1.add(7);
  t1.add(5);
  cout << "t1: " << t1 << endl;
  ThreadedBST t2(t1);
  t2.add(11);
  assert(t1.getNumberOfNodes() != t2.getNumberOfNodes());
  cout << "t2: " << t2 << endl;
  cout << "t1: " << t1 << endl;
}

void test3() // sort a vector of values for balanced tree
{
  ThreadedBST t1{};
  vector<int> values = {1, 2, 3, 4, 5, 6};
  // add 3, 1, 2, 5, 4, 6
  vector<int> valuesSorted = {};
  t1.sortVector(values, valuesSorted, 0, values.size() - 1);
  cout << "sorted value array size: " << valuesSorted.size() << endl;
  for (int i = 0; i < valuesSorted.size(); i++)
  {
    cout << valuesSorted[i] << " ";
  }
  cout << endl;
}

// asks for value n and makes first tree with values 1 - n, displays inorder, then makes copy and deletes all even values from copy
void finalTest()
{
  int n;
  vector<int> values = {}; // values to insert
  vector<int> valuesSorted = {}; // list with values sorted for insertion
  ThreadedBST tree1{};

  cout << "Pick any positive integer: ";
  cin >> n;

  // populate the values vector from 1 to n
  for (int i = 1; i <= n; i++)
  {
    values.push_back(i);
  }

  // prepare the valuesSorted vector for insertion
  tree1.sortVector(values, valuesSorted, 0, values.size() - 1);

  // add values to tree
  for (int i = 0; i < valuesSorted.size(); i++)
  {
    tree1.add(valuesSorted[i]);
  }

  cout << "First tree: " << tree1 << endl;

  // copy tree1 to tree2
  ThreadedBST tree2(tree1);

  cout << "Second tree with even values: " << tree2 << endl;

  if (values.size() > 1)
  {
    for (int i = 1; i < values.size(); i += 2)
    {
      tree2.remove(values[i]);
    }
  }

  cout << "Second tree without even values: " << tree2 << endl;
}

int main()
{
  //test0();
  //test1();
  //test2();
  //test3();
  finalTest();

  return 0;
}