#include <cassert>
#include <iostream>

#include "skiplist.h"

using namespace std;

void test0()
{
   srand(time(0)); // seed for generating random numbers
   SkipList s1(3, 60);
   // cout << s1 << endl;
   s1.add(3);
   s1.add(20);
   assert(s1.contains(3));
   assert(s1.contains(20));
   assert(!s1.contains(-14));
   assert(!s1.add(3));
   assert(s1.add(vector<int>{1, -7, 0}));
   assert(!s1.add(vector<int>{-1, 421472193, -1}));

   cout << s1 << endl;
   assert(!SkipList(1, 99).contains(0));

   assert(s1.remove(3));
   assert(!s1.remove(202020));
   assert(s1.add(1478));
}

void test1()
{
   // setting seed for easy testing
   srand(10000);
   SkipList skp(5, 80);
   cout << boolalpha;
   skp.add(3);
   skp.add(5);
   skp.add(vector<int>{1, 7, 9});
   // cannot add existing
   assert(!skp.add(vector<int>{1, 7}));
   cout << skp << endl;
   cout << "7 ? " << skp.contains(7) << endl;
   cout << "3 ? " << skp.contains(3) << endl;
   cout << "-100 ? " << skp.contains(-100) << endl;
   cout << "100 ? " << skp.contains(100) << endl;

   bool result = skp.remove(5);
   assert(result);
   result = skp.remove(5);
   assert(!result);
   cout << skp << endl;
}

int main()
{
   test0();
   test1();

   cout << "Done." << endl;
   return 0;
}