#include "Index.h"


#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void visit(shared_ptr<string> key, int value)
{
   cout << *key << ", " << value << endl;
}

// void InOrderVisit(function<void(shared_ptr<string>, int)> visit)
// {
//    visit(make_shared<string>("hihi"), 5);
// }

int main()
{
   Index i{};

   i.parseBook();
   i.InOrderVisit(&visit);

   return 0;
}