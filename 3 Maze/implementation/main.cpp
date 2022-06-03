#include <cassert>
#include <iostream>
#include <sstream>

#include "creature.h"
#include "maze.h"


void test()
{
   Maze M("maze.txt");
   Creature C(4, 4);
   stringstream ss;

   // cout << M << endl;  // print initial maze
   // cout << "Path: " << C.solve(M) << endl;  // print path

   assert(C.solve(M) == "EEENNNEEEEEESEESSSEEENNNNN");
   ss << C;

   cout << M << endl;  // print solved maze
   // cout << C << endl; // print creature
   // cout << ss.str() << endl; // print stringstream
   // cout << M; // print solved maze 
   assert(ss.str() == "C(0, 18)");
   cout << "Test 0 Passed!" << endl;
}

void test1()
{
   Maze M("maze1.txt");
   Creature C(26, 20);
   stringstream ss;

   cout << M << endl;  // print initial maze
   // cout << "Path: " << C.solve(M) << endl;  // print path
   // cout << M << endl;  // print solved maze

   assert(C.solve(M) == "NNNNNNNNNNNNNNNNNNNNNNNNNWWWWWSSSWWWWWWWWWWEEEEESSSEEEEEEEEEEEEEESSSSSSSSSSEEEEENSSSSWWWWWWWWEEEEEEEEEESSSSSSSSSSSSSWWWWWWWWWWWWSSSSSSSSSSEEEEEEEEEEEEEENNNNNNNNWWWWWWWWWWWWSSSSSSEEEESSSSSSSSSSSSWWWWWWWWWWWWWWWWWWWNNNNNNNNNNNNNNNNNNNNNWWWWWWWWWWWWWWWWWWWW");
   ss << C;
   cout << M << endl;  // print solved maze
   // cout << C << endl; // print creature
   // cout << ss.str() << endl; // print stringstream
   // cout << M; // print solved maze 
   assert(ss.str() == "C(41, 0)");

   cout << "Test 1 Passed!" << endl;
}

void test2()
{
   Maze M("maze2.txt");
   Creature C(1, 1);
   stringstream ss;

   cout << M << endl;  // print initial maze
   // cout << "Path: " << C.solve(M) << endl;  // print path
   // cout << M << endl;  // print solved maze

   assert(C.solve(M).empty());
   ss << C;
   cout << M << endl;  // print solved maze
   // cout << C << endl; // print creature
   // cout << ss.str() << endl; // print stringstream
   // cout << M; // print solved maze 
   assert(ss.str() == "C(1, 1)");

   cout << "Test 2 Passed!" << endl;
}

void test3()
{
   Maze M("maze3.txt");
   Creature C(1, 1);
   stringstream ss;

   cout << M << endl;  // print initial maze
   // cout << "Path: " << C.solve(M) << endl;  // print path
   // cout << M << endl;  // print solved maze

   assert(C.solve(M) == "EEEEEENEEEEEESEESSSEEENNNNNSSSWWWWSS");
   ss << C;
   cout << M << endl;  // print solved maze
   // cout << C << endl; // print creature
   // cout << ss.str() << endl; // print stringstream
   // cout << M; // print solved maze 
   assert(ss.str() == "C(6, 3)");

   cout << "Test 3 Passed!" << endl;
}

int main()
{
    test();
    test1();
    test2();
    test3();
    cout << endl << "All tests completed!" << endl;
    return 0;
}